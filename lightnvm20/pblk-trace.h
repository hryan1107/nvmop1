/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM pblk

#if !defined(_TRACE_PBLK_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_PBLK_H

#include <linux/tracepoint.h>

struct ppa_addr;

#define show_chunk_flags(state) __print_flags(state, "",	\
	{ NVM_CHK_ST_FREE,		"FREE",		},	\
	{ NVM_CHK_ST_CLOSED,		"CLOSED",	},	\
	{ NVM_CHK_ST_OPEN,		"OPEN",		},	\
	{ NVM_CHK_ST_OFFLINE,		"OFFLINE",	})

#define show_line_state(state) __print_symbolic(state,		\
	{ PBLK_LINESTATE_NEW,		"NEW",		},	\
	{ PBLK_LINESTATE_FREE,		"FREE",		},	\
	{ PBLK_LINESTATE_OPEN,		"OPEN",		},	\
	{ PBLK_LINESTATE_CLOSED,	"CLOSED",	},	\
	{ PBLK_LINESTATE_GC,		"GC",		},	\
	{ PBLK_LINESTATE_BAD,		"BAD",		},	\
	{ PBLK_LINESTATE_CORRUPT,	"CORRUPT"	})


#define show_pblk_state(state) __print_symbolic(state,		\
	{ PBLK_STATE_RUNNING,		"RUNNING",	},	\
	{ PBLK_STATE_STOPPING,		"STOPPING",	},	\
	{ PBLK_STATE_RECOVERING,	"RECOVERING",	},	\
	{ PBLK_STATE_STOPPED,		"STOPPED"	})

#define show_chunk_erase_state(state) __print_symbolic(state,	\
	{ PBLK_CHUNK_RESET_START,	"START",	},	\
	{ PBLK_CHUNK_RESET_DONE,	"OK",		},	\
	{ PBLK_CHUNK_RESET_FAILED,	"FAILED"	})


TRACE_EVENT(pblk_chunk_reset,

	TP_PROTO(const char *name, struct ppa_addr *ppa, int state),

	TP_ARGS(name, ppa, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(u64, ppa)
		__field(int, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->ppa = ppa->ppa;
		__entry->state = state;
	),

	TP_printk("dev=%s grp=%llu pu=%llu chk=%llu state=%s", __get_str(name),
			(u64)(((struct ppa_addr *)(&__entry->ppa))->m.grp),
			(u64)(((struct ppa_addr *)(&__entry->ppa))->m.pu),
			(u64)(((struct ppa_addr *)(&__entry->ppa))->m.chk),
			show_chunk_erase_state((int)__entry->state))

);

TRACE_EVENT(pblk_chunk_state,

	TP_PROTO(const char *name, struct ppa_addr *ppa, int state),

	TP_ARGS(name, ppa, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(u64, ppa)
		__field(int, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->ppa = ppa->ppa;
		__entry->state = state;
	),

	TP_printk("dev=%s grp=%llu pu=%llu chk=%llu state=%s", __get_str(name),
			(u64)(((struct ppa_addr *)(&__entry->ppa))->m.grp),
			(u64)(((struct ppa_addr *)(&__entry->ppa))->m.pu),
			(u64)(((struct ppa_addr *)(&__entry->ppa))->m.chk),
			show_chunk_flags((int)__entry->state))

);

TRACE_EVENT(pblk_line_state,

	TP_PROTO(const char *name, int line, int state),

	TP_ARGS(name, line, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(int, line)
		__field(int, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->line = line;
		__entry->state = state;
	),

	TP_printk("dev=%s line=%d state=%s", __get_str(name),
			(int)__entry->line,
			show_line_state((int)__entry->state))

);

TRACE_EVENT(pblk_state,

	TP_PROTO(const char *name, int state),

	TP_ARGS(name, state),

	TP_STRUCT__entry(
		__string(name, name)
		__field(int, state)
	),

	TP_fast_assign(
		__assign_str(name, name);
		__entry->state = state;
	),

	TP_printk("dev=%s state=%s", __get_str(name),
			show_pblk_state((int)__entry->state))

);

/* NTU NVM OCSSD Start */
/* ret = 1 -> requeue */
/* (Number of inbound bio sectors, is_requeue) */
TRACE_EVENT(pblk_io_resch,

    TP_PROTO(int nr_entries, int ret),

    TP_ARGS(nr_entries, ret),

    TP_STRUCT__entry(
        __field(int, nr_entries)
        __field(int, ret)
    ),

    TP_fast_assign(
        __entry->nr_entries = nr_entries;
        __entry->ret = ret;
    ),
	
    TP_printk("%d , %d", (int)__entry->nr_entries, (int)__entry->ret)

);

/* Print LBA on read io */
/* 
	type: io type
	seq: sector seq
	size: io size
	lba: 4k-sector logical address
	cached: cache hit
	
	format: (type, seq, size, lba, cached)
*/
TRACE_EVENT(pblk_pr_read_io,
    TP_PROTO(const char *type, int seq, int size, u64 lba, bool cached),

    TP_ARGS(type, seq, size, lba, cached),

    TP_STRUCT__entry(
		__string(type, type)
        __field(int, seq)
        __field(int, size)
        __field(u64, lba)
        __field(bool, cached)
    ),

    TP_fast_assign(
		__assign_str(type, type);
        __entry->seq = seq;
        __entry->size = size;
        __entry->lba = lba;
        __entry->cached = cached;
    ),

    TP_printk("(%s, %d, %d, %llu, %d)", __get_str(type), (int)__entry->seq, (int)__entry->size, (u64)__entry->lba, (bool)__entry->cached)
);

/* Print LBA on write io */
/* 
	type: io type
	seq: sector seq
	size: io size
	lba: 4k-sector logical address

	format: (type, seq, size, lba) 
*/
TRACE_EVENT(pblk_pr_write_io,
    TP_PROTO(const char *type, int seq, int size, u64 lba),

    TP_ARGS(type, seq, size, lba),

    TP_STRUCT__entry(
		__string(type, type)
        __field(int, seq)
        __field(int, size)
        __field(u64, lba)
    ),

    TP_fast_assign(
		__assign_str(type, type);
        __entry->seq = seq;
        __entry->size = size;
        __entry->lba = lba;
    ),

    TP_printk("(%s, %d, %d, %llu)", __get_str(type), (int)__entry->seq, (int)__entry->size, (u64)__entry->lba)
);

/* sectors submitted from buffer to ssd*/
TRACE_EVENT(pblk_write_secs,

    TP_PROTO(long nr_secs),

    TP_ARGS(nr_secs),

    TP_STRUCT__entry(
        __field(long, nr_secs)
    ),

    TP_fast_assign(
        __entry->nr_secs = nr_secs;
    ),

    TP_printk("%ld", (int)__entry->nr_secs)
);

TRACE_EVENT(pblk_gc_acct,


);
/* NTU NVM OCSSD END */




#endif /* !defined(_TRACE_PBLK_H) || defined(TRACE_HEADER_MULTI_READ) */

/* This part must be outside protection */

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH ../../drivers/lightnvm
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE pblk-trace
#include <trace/define_trace.h>
