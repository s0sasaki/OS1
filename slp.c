#include "param.h"
#include "proc.h"
#include "user.h"
#include "malloc.h"
#include "systm.h"
#include "prf.h"

/*
 * Give up the processor till a wakeup occurs
 * on chan, at which time the process
 * enters the scheduling queue at priority pri.
 * The most important effect of pri is that when
 * pri<0 a signal cannot disturb the sleep;
 * if pri>=0 signals will be processed.
 * Callers of this routine must be prepared for
 * premature return, and check that the reason for
 * sleeping has gone away.
 */
void sleep(int chan, char pri)
{
	//register *rp, s;
	register struct proc *rp;

	//s = PS->integ;
	rp = u.u_procp;
	if(pri >= 0) {
		//if(issig())
		//	goto psig;
		//spl6();
		rp->p_wchan = chan;
		rp->p_stat = SWAIT;
		rp->p_pri = pri;
		//spl0();
		if(runin != 0) {
			runin = 0;
			//wakeup(&runin);
		}
		swtch();
		//if(issig())
		//	goto psig;
	} else {
		//spl6();
		rp->p_wchan = chan;
		rp->p_stat = SSLEEP;
		rp->p_pri = pri;
		//spl0();
		swtch();
	}
	//PS->integ = s;
	return;

	/*
	 * If priority was low (>=0) and
	 * there has been a signal,
	 * execute non-local goto to
	 * the qsav location.
	 * (see trap1/trap.c)
	 */
//psig:
//	aretu(u.u_qsav);
}

/*
 * This routine is called to reschedule the CPU.
 * if the calling process is not in RUN state,
 * arrangements for it to restart must have
 * been made elsewhere, usually by calling via sleep.
 */
int swtch()
{
	static struct proc *p;
	register int i, n;
	register struct proc *rp;

	if(p == NULL)
		p = &proc[0];
	/*
	 * Remember stack of caller
	 */
	//savu(u.u_rsav);
	/*
	 * Switch to scheduler's stack
	 */
	//retu(proc[0].p_addr);

loop:
	runrun = 0;
	rp = p;
	p = NULL;
	n = 128;
	/*
	 * Search for highest-priority runnable process
	 */
	i = NPROC;
	do {
		rp++;
		if(rp >= &proc[NPROC])
			rp = &proc[0];
		if(rp->p_stat==SRUN && (rp->p_flag&SLOAD)!=0) {
			if(rp->p_pri < n) {
				p = rp;
				n = rp->p_pri;
			}
		}
	} while(--i);
	/*
	 * If no process is runnable, idle.
	 */
	if(p == NULL) {
		p = rp;
		//idle();
		goto loop;
	}
	rp = p;
	curpri = n;
	/*
	 * Switch to stack of the new process and set up
	 * his segmentation registers.
	 */
	//retu(rp->p_addr);
	//sureg();
	/*
	 * If the new process paused because it was
	 * swapped out, set the stack level to the last call
	 * to savu(u_ssav).  This means that the return
	 * which is executed immediately after the call to aretu
	 * actually returns from the last routine which did
	 * the savu.
	 *
	 * You are not expected to understand this.
	 */
	if(rp->p_flag&SSWAP) {
		rp->p_flag &= ~SSWAP;
		//aretu(u.u_ssav);
	}
	/*
	 * The value returned here has many subtle implications.
	 * See the newproc comments.
	 */
	return(1);
}

/*
 * Create a new process-- the internal version of
 * sys fork.
 * It returns 1 in the new process.
 * How this happens is rather hard to understand.
 * The essential fact is that the new process is created
 * in such a way that appears to have started executing
 * in the same call to newproc as the parent;
 * but in fact the code that runs is that of swtch.
 * The subtle implication of the returned value of swtch
 * (see above) is that this is the value that newproc's
 * caller in the new process sees.
 */
int newproc()
{
	int a1, a2;
	struct proc *p, *up;
	register struct proc *rpp;
	//register *rip, n;
	register struct proc *rip;
    unsigned int n;

	p = NULL;
	/*
	 * First, just locate a slot for a process
	 * and copy the useful info from this process into it.
	 * The panic "cannot happen" because fork has already
	 * checked for the existence of a slot.
	 */
retry:
	mpid++;
	if(mpid < 0) {
		mpid = 0;
		goto retry;
	}
	for(rpp = &proc[0]; rpp < &proc[NPROC]; rpp++) {
		if(rpp->p_stat == NULL && p==NULL)
			p = rpp;
		if (rpp->p_pid==mpid)
			goto retry;
	}
	if ((rpp = p)==NULL)
		panic("no procs");

	/*
	 * make proc entry for new proc
	 */

	rip = u.u_procp;
	up = rip;
	rpp->p_stat = SRUN;
	rpp->p_flag = SLOAD;
	rpp->p_uid = rip->p_uid;
	rpp->p_ttyp = rip->p_ttyp;
	rpp->p_nice = rip->p_nice;
	rpp->p_textp = rip->p_textp;
	rpp->p_pid = mpid;
	rpp->p_ppid = rip->p_pid;
	rpp->p_time = 0;

	/*
	 * make duplicate entries
	 * where needed
	 */
	//for(rip = &u.u_ofile[0]; rip < &u.u_ofile[NOFILE];)
	//	if((rpp = *rip++) != NULL)
	//		rpp->f_count++;
	//if((rpp=up->p_textp) != NULL) {
	//	rpp->x_count++;
	//	rpp->x_ccount++;
	//}
	//u.u_cdir->i_count++;

	/*
	 * Partially simulate the environment
	 * of the new process so that when it is actually
	 * created (by copying) it will look right.
	 */
	//savu(u.u_rsav);
	//rpp = p;
	//u.u_procp = rpp;
	//rip = up;
	//n = rip->p_size;
	//a1 = rip->p_addr;
	//rpp->p_size = n;
	//a2 = malloc(coremap, n);

	/*
	 * If there is not enough core for the
	 * new process, swap out the current process to generate the
	 * copy.
	 */
	//if(a2 == NULL) {
	//	rip->p_stat = SIDL;
	//	rpp->p_addr = a1;
	//	savu(u.u_ssav);
	//	xswap(rpp, 0, 0);
	//	rpp->p_flag =| SSWAP;
	//	rip->p_stat = SRUN;
	//} else {

	/*
	 * There is core, so just copy.
	 */
	//	rpp->p_addr = a2;
	//	while(n--)
	//		copyseg(a1++, a2++);
	//}
	//u.u_procp = rip;
	return(0);
}

