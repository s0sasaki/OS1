/*
 * One structure allocated per active
 * process. It contains all data needed
 * about the process while the
 * process may be swapped out.
 * Other per process data (user.h)
 * is swapped with the process.
 */
struct	proc
{
	char	p_stat;		
	char	p_flag;		
	char	p_pri;		
	char	p_sig;		
	char	p_uid;		
	char	p_time;		
	char	p_cpu;		
	char	p_nice;		
	int	p_ttyp;		
	int	p_pid;		
	int	p_ppid;		
	int	p_addr;		
	int	p_size;		
	int	p_wchan;	
	int	*p_textp;	
} proc[NPROC];

/* stat codes */
#define	SSLEEP	1		
#define	SWAIT	2		
#define	SRUN	3		
#define	SIDL	4		
#define	SZOMB	5		
#define	SSTOP	6		

/* flag codes */
#define	SLOAD	01		/* in core */
#define	SSYS	02		/* scheduling process */
#define	SLOCK	04		/* process cannot be swapped */
#define	SSWAP	010		/* process is being swapped out */
#define	STRC	020		/* process is being traced */
#define	SWTED	040		/* another tracing flag */
