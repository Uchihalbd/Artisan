#ifndef ART_RUNTIME_TWODROID_PROBE_H_
#define ART_RUNTIME_TWODROID_PROBE_H_

#include "twodroid/Constant.h"
#include "interpreter/interpreter_common.h"

namespace gossip{

//extern "C" {
	void diaos_start();
	bool diaos_check();
	bool diaos_init();
	void diaos_prepare();
	void diaos_monitor_func_call( const char * myclass, const char* mymethod, const char* retype, const char * currentclass);
	void diaos_monitor_parameter_art( art::mirror::ArtMethod* method, art::ShadowFrame& shadow_frame, const art::Instruction* inst, uint16_t inst_data, bool is_range) SHARED_LOCKS_REQUIRED(art::Locks::mutator_lock_);
	void diaos_monitor_parameter( u4* pr, art::mirror::ArtMethod*  method) SHARED_LOCKS_REQUIRED(art::Locks::mutator_lock_);


	bool diaos_oat_check();
	void diaos_log_oat(const std::string& filename, const std::string& location);
	void diaos_unpack( art::mirror::ArtMethod*  method) SHARED_LOCKS_REQUIRED(art::Locks::mutator_lock_);


	//void setEP(const void* ep1);
    //const void* getEP();
    void setEP(const char* flag, const void* ep1);

    const void* getEP(const char* flag);

    bool class_should_be_traced(const char * myclass);


//}//end of  extern "C"


}//end of namespace

#endif