// implement fork from user space

#include <inc/string.h>
#include <inc/lib.h>

// PTE_COW marks copy-on-write page table entries.
// It is one of the bits explicitly allocated to user processes (PTE_AVAIL).
#define PTE_COW		0x800

//
// Custom page fault handler - if faulting page is copy-on-write,
// map in our own private writable copy.
//
static void
pgfault(struct UTrapframe *utf)
{
	void *addr = (void *) utf->utf_fault_va;
	uint32_t err = utf->utf_err;
	int r;

	// Check that the faulting access was (1) a write, and (2) to a
	// copy-on-write page.  If not, panic.
	// Hint:
	//   Use the read-only page table mappings at uvpt
	//   (see <inc/memlayout.h>).

	// LAB 4: Your code here.
	if (!((uvpt[PGNUM(addr)]) & PTE_COW)) {
		cprintf("addr {0x%08x}\n", addr);
		panic("panic in pgfault\n");
	}

	// Allocate a new page, map it at a temporary location (PFTEMP),
	// copy the data from the old page to the new page, then move the new
	// page to the old page's address.
	// Hint:
	//   You should make three system calls.

	// LAB 4: Your code here.
	void *va = (void*)ROUNDDOWN(addr, PGSIZE);

	uint32_t perm = uvpt[PGNUM(addr)] & 0x3ff;
	perm &= 0xf;
	perm &= ~PTE_COW;
	perm |= PTE_W;

	if ((r = sys_page_alloc(0, PFTEMP, perm)) < 0) {
		panic("panic in pgfault 2\n");
	}

	// copy data from cow page to PFTEMP
	memmove(PFTEMP, va, PGSIZE);

	if ((r = sys_page_unmap(0, va)) < 0) {
		panic("panic in pgfault 3\n");
	}

	if ((r = sys_page_map(0, PFTEMP, 0, va, perm)) < 0) {
		panic("panic in pgfault 4\n");
	}

	if ((r = sys_page_unmap(0, PFTEMP)) < 0) {
		panic("panic in pgfault 5\n");
	}

	// panic("pgfault not implemented");
}

//
// Map our virtual page pn (address pn*PGSIZE) into the target envid
// at the same virtual address.  If the page is writable or copy-on-write,
// the new mapping must be created copy-on-write, and then our mapping must be
// marked copy-on-write as well.  (Exercise: Why do we need to mark ours
// copy-on-write again if it was already copy-on-write at the beginning of
// this function?)
//
// Returns: 0 on success, < 0 on error.
// It is also OK to panic on error.
//
static int  
duppage(envid_t envid, unsigned pn) 
{
  int r;

  // LAB 4: Your code here.
  // panic("duppage not implemented");
  void *va = (void*)(pn * PGSIZE);
  uint32_t perm = 0;

  // Judge whether the page is copy-on-write page
  if ((uvpt[pn] & PTE_P) && (uvpt[pn] & PTE_U) &&
      (((uvpt[pn] & PTE_W) && !(uvpt[pn] & PTE_COW)) ||
       (!(uvpt[pn] & PTE_W) && (uvpt[pn] & PTE_COW))) ) {
    // page is copy-on-write page.
    // set child's page perm with PTW_COW
    perm = uvpt[pn] & 0xFFF;
    perm |= PTE_COW;
    perm &= ~PTE_W;
    if ((r = sys_page_map(0, va, envid, va, perm)) < 0) {
			cprintf("pn = %d\n", pn);
			cprintf("pn_pgaddr = 0x%08x\n", pn * PGSIZE);
      panic("panic within duppage funcion. 1 \n");
    }

    // reset parent's page perm with PTE_COW
    if ((r = sys_page_map(0, va, 0, va, perm)) < 0) {
      panic("panic within duppage funcion. 2 \n");
    }
  } else if ((uvpt[pn] & PTE_P) && (uvpt[pn] & PTE_U) &&
             !((uvpt[pn]) & PTE_W) && !(uvpt[pn] & PTE_COW)) {
    // the page is read-only page.
    perm = uvpt[pn] & 0xFFF;
    if ((r = sys_page_map(0, va, envid, va, perm)) < 0) {
      panic("panic within duppage funcion. 3 \n");
    }
  } else {
    panic("panic within duppage funcion. 4 \n");
  }

  return 0;
}

//
// User-level fork with copy-on-write.
// Set up our page fault handler appropriately.
// Create a child.
// Copy our address space and page fault handler setup to the child.
// Then mark the child as runnable and return.
//
// Returns: child's envid to the parent, 0 to the child, < 0 on error.
// It is also OK to panic on error.
//
// Hint:
//   Use uvpd, uvpt, and duppage.
//   Remember to fix "thisenv" in the child process.
//   Neither user exception stack should ever be marked copy-on-write,
//   so you must allocate a new page for the child's user exception stack.
//
envid_t
fork(void)
{
  // LAB 4: Your code here.
  // panic("fork not implemented");
  set_pgfault_handler(pgfault);

  // Create a child.
  envid_t child_id = sys_exofork();

  if (child_id == 0) {
    // Fix "thisenv" in the child process.
    thisenv = &envs[ENVX(sys_getenvid())];

    return 0;
  }

  // Copy our address space to the child.
  extern unsigned char end[];
  for (uint8_t *va = (uint8_t *)UTEXT; va < end; va += PGSIZE) {
    duppage(child_id, PGNUM(va));
  }

  int r = 0;
  // Page fault handler setup to the child.
  // set_pgfault_handler(pgfault);
  if ((r = sys_page_alloc(child_id, (void *)(UXSTACKTOP - PGSIZE),
                          PTE_P | PTE_W | PTE_U)) < 0)
    panic("page in fork\n");

  extern void _pgfault_upcall(void);
  if ((r = sys_env_set_pgfault_upcall(child_id, _pgfault_upcall)) < 0)
    panic("page in fork\n");

  // Alloc child stack
	if ((r = sys_page_alloc(child_id, (void*)(USTACKTOP - PGSIZE), PTE_P|PTE_U|PTE_W)) < 0)
		panic("sys_page_alloc: %e", r);
	if ((r = sys_page_map(child_id, (void*)(USTACKTOP - PGSIZE), 0, UTEMP, PTE_P|PTE_U|PTE_W)) < 0)
		panic("sys_page_map: %e", r);
	
	// Copy stack 
	memmove(UTEMP, (void*)(USTACKTOP - PGSIZE), PGSIZE);
	if ((r = sys_page_unmap(0, UTEMP)) < 0)
		panic("sys_page_unmap: %e", r);

  // Mark the child as "runnable".
  if ((r = sys_env_set_status(child_id, ENV_RUNNABLE))< 0)
    panic("page in fork\n");

  return child_id;
}

// Challenge!
int
sfork(void)
{
	panic("sfork not implemented");
	return -E_INVAL;
}
