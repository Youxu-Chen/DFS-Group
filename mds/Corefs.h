#ifndef CEPH_COREFS_MDS_SERVER_H
#define CEPH_COREFS_MDS_SERVER_H

#include "MDSRank.h"
#include "Server.h"

#include <boost/lexical_cast.hpp>
#include "include/assert.h"  // lexical_cast includes system assert.h

#include <boost/config/warning_disable.hpp>
#include <boost/fusion/include/std_pair.hpp>

#include "MDSRank.h"
#include "Server.h"
#include "Locker.h"
#include "MDCache.h"
#include "MDLog.h"
#include "Migrator.h"
#include "MDBalancer.h"
#include "InoTable.h"
#include "SnapClient.h"
#include "Mutation.h"

#include "msg/Messenger.h"

#include "osdc/Objecter.h"

#include "messages/MClientSession.h"
#include "messages/MClientRequest.h"
#include "messages/MClientReply.h"
#include "messages/MClientReconnect.h"
#include "messages/MClientCaps.h"
#include "messages/MClientSnap.h"

#include "messages/MMDSSlaveRequest.h"

#include "messages/MLock.h"

#include "events/EUpdate.h"
#include "events/ESlaveUpdate.h"
#include "events/ESession.h"
#include "events/EOpen.h"
#include "events/ECommitted.h"

#include "include/filepath.h"
#include "common/errno.h"
#include "common/Timer.h"
#include "common/perf_counters.h"
#include "include/compat.h"
#include "osd/OSDMap.h"

#include <errno.h>
#include <fcntl.h>

#include <list>
#include <iostream>
using namespace std;

#include "common/config.h"
#define dout_subsys ceph_subsys_mds
#undef dout_prefix
#define dout_prefix *_dout << "mds." << mds->get_nodeid() << ".server "

class OSDMap;
class PerfCounters;
class LogEvent;
class EMetaBlob;
class EUpdate;
class MMDSSlaveRequest;
struct SnapInfo;
class MClientRequest;
class MClientReply;
class MDLog;

struct MutationImpl;
struct MDRequestImpl;
typedef ceph::shared_ptr<MutationImpl> MutationRef;
typedef ceph::shared_ptr<MDRequestImpl> MDRequestRef;

void Server::corefs_print_xattrs(CInode *in){
	map<string, bufferptr>::iterator iter;
  	dout(1) << __func__ << dendl;

  	for(iter=in->xattrs.begin(); iter!=in->xattrs.end(); iter++)
    	dout(1) << __func__ << " " << iter->first << dendl;
	// string s = "corefs.correlation";
	// void *tmp;
	// char *c = NULL;
	// uint64_t len;

	// map<string,bufferptr> *px = in->get_projected_xattrs();
	// if((len = (*px)[s].length()) > 0){
	// 	tmp = (void *)malloc(sizeof(char) * (len + 1));
	// 	memcpy(tmp, (*px)[s].c_str(), len);
	// 	c = (char*)tmp;
	// 	c[len - 1] = 0;
	// }
	// dout(1) << __func__ << " corefs get xattrs:<" << s <<", " << c <<"> from CInode" << dendl;
}

char* Server::corefs_get_xattrs(CInode *cin){
	char *c = NULL;
	map<string, bufferptr>::iterator p = cin->xattrs.begin();
	c = const_cast<char*>(p->first.c_str());
	// string type_correlation = "corefs.correlation";
	// void *tmp;
	// char* c = NULL;
	// uint64_t len;

	// map<string,bufferptr> *px = cin->get_projected_xattrs();
	// if((len = (*px)[type_correlation].length()) > 0){
	// 	tmp = (void *)malloc(sizeof(char) * (len));
	// 	memcpy(tmp, (*px)[type_correlation].c_str(), len);
	// 	c = (char*)tmp;
	// 	c[len - 1] = 0;
	// }
	
	// dout(1) << __func__ << " corefs get xattrs:<" << type_correlation <<", " << c <<"> from CInode" << dendl;
	return c;
}

int Server::corefs_get_correlations(CInode *target, char** c){
	*c = corefs_get_xattrs(target);
	if(*c == NULL)
		return 0;
	return 1;
}

CInode* Server::corefs_prefetch_cinode(char* filename){
	dout(1) << __func__ << " filename = " << filename << dendl;
	filepath path(filename);
	CInode *cur = mdcache->cache_traverse(path);
	if(cur)
		return cur;
	return NULL;
}

// int r = mdcache->path_traverse(mdr, NULL, NULL, refpath, &mdr->dn[n], &mdr->in[n], MDS_TRAVERSE_FORWARD);

// int MDCache::path_traverse(MDRequestRef& mdr, Message *req, MDSInternalContextBase *fin,     // who
// 			   const filepath& path,                   // what
//                            vector<CDentry*> *pdnvec,         // result
// 			   CInode **pin,
//                            int onfail)

// vector<CDentry*> Server::corefs_prefetch_dentry(char *filename){
	
// }

#endif