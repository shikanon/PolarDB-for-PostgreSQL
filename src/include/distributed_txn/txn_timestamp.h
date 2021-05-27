/*-------------------------------------------------------------------------
 *
 * txn_timestamp.h
 *
 * Portions Copyright (c) 1996-2018, PostgreSQL Global Development Group
 * Portions Copyright (c) 1994, Regents of the University of California
 *
 * src/include/distributed_txn/txn_timestamp.h
 *
 *-------------------------------------------------------------------------
 */
#ifndef DISTRIBUTED_TXN_TIMESTAMP_H
#define DISTRIBUTED_TXN_TIMESTAMP_H

#include "postgres.h"

#include "distributed_txn/logical_clock.h"

extern bool enable_timestamp_debug_print;

typedef bool (*IsCoordinating2PCHook)(void);
extern IsCoordinating2PCHook IsCoordinating2PC;

/**
 * start_ts: generated by ClockNow() at GetSnapshotData, 
 *              or assigned from coordinator
 * prepare_ts: generated by ClockTick() as PrepareTransaction
 * commit_ts: generated by ClockTick() at TransactionIdAsyncCommitTree, 
 *              or assigned from coordinator
 * coordinated_commit_ts: decided by Max{prepare_ts} during 2PC
 */
extern void AtEOXact_txn(void);
extern void TxnSetCoordinatedCommitTs(LogicalTime);
extern void TxnSetCoordinatedCommitTsFromStr(const char *);
extern LogicalTime TxnGetStartTs(void);
extern LogicalTime TxnGetCoordinatedCommitTs(void);
extern LogicalTime TxnGetOrGenerateStartTs(bool latest);
extern LogicalTime TxnGetOrGenerateCommitTs(bool fromCoordinator);

/**
 * Reply prepare_ts, commit_ts through libpq
 */
void TxnSetReplyTimestamp(LogicalTime ts);
LogicalTime TxnGetAndClearReplyTimestamp(void);

void BackendRecvTimestamp(LogicalTime ts);
void FrontendRecvTimestamp(LogicalTime ts);

/*
Datum txn_set_start_ts(start_ts);
Datum txn_get_start_ts();
Datum txn_get_prepare_ts();
Datum txn_set_commit_ts(commit_ts);
*/

#endif /* DISTRIBUTED_TXN_TIMESTAMP_H */