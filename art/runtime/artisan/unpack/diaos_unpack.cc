#include "twodroid/unpack/diaos_unpack.h"
#include <fstream>
#include <string.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include <iostream>
#include "bytestream.h"
#include "dex_file.h"
#include "leb128.h"
#include "twodroid/Constant.h"

using ::art::DexFile;


namespace gossip {
	/*
	int GetStrData(const art::DexFile* df,const DexFile::Header& dh,std::vector<const u1*>* v_StrData, std::vector<int>* v_StrDataLength);
	int GetTypeList(const DexFile* df,const DexFile::Header& dh,std::vector<const u1*>* v_TypelistData,std::vector<int>* v_TypelistSize);
	int GetEncoded(const DexFile* df,const DexFile::Header& dh,std::vector<const u1*>* v_EncodedData,std::vector<int>* v_EncodedSize);
	void BuildHeader(ByteStream* bs, int offset, const DexFile::Header& dh);
	void dxb_header(ByteStream *bs, const DexFile::Header& header, uint32_t offset);
	int read_strdata_length(const u1* str);
	int read_typelist_length(const u1* tyl);
	int read_encodedarray_length(const u1* ea);
	*/
	void dexbuild(const art::DexFile*  df, const char* filename){
		const DexFile::Header& dh = df->GetHeader();
		ByteStream* bs = bsalloc(dh.file_size_);
		bsseek(bs,0);
		bswrite(bs,(u1*)df->Begin(),dh.file_size_);
		bssave(bs,filename);
        bsfree(bs);


    /*
		LOG(WARNING) << "UCHIHALART----------------------DEX BUILD START";
		const DexFile::Header& dh = df->GetHeader();
		//-------------------------------------------------------------------------------declare Objects
		//int baseAddr = 0;
		//int StrIDAddr = sizeof(DexFile::Header);
		//int TypeIDAddr = StrIDAddr + dh.string_ids_size_ * sizeof(DexFile::StringId);
		//int ProtoIDAddr = TypeIDAddr + dh.type_ids_size_ * sizeof(DexFile::TypeId);
		//int FiledIDAddr = ProtoIDAddr + dh.proto_ids_size_ * sizeof(DexFile::ProtoId);
		//int MethodIDAddr = FiledIDAddr + dh.field_ids_size_ * sizeof(DexFile::FieldId);
		//int ClassDefAddr = MethodIDAddr + dh.method_ids_size_ * sizeof(DexFile::MethodId);
		//int MapAddr = ClassDefAddr + dh.class_defs_size_ * sizeof(DexFile::ClassDef);

		//int TypeListAddr = MapAddr+4+18*sizeof(DexFile::MapItem);
		//int ClassDataAddr = 0;
		//int CodeAddr = 0;
		//int StrDataAddr = 0;
		//int DebugAddr = 0;
		//int EncodedAddr = 0;
		//int EndAddr = 0;

		//-----------------------------------------------------------------------------get Data
		std::vector<const u1*>* v_StrData = new std::vector<const u1*>;
    	std::vector<int>* v_StrDataLength = new std::vector<int>;
    	int StrDataSize = GetStrData(df,dh,v_StrData,v_StrDataLength);

    	std::vector<const u1*>* v_TypelistData = new std::vector<const u1*>;
  	    std::vector<int>* v_TypelistSize=new std::vector<int>;
        int TypelistSize = GetTypeList(df,dh,v_TypelistData,v_TypelistSize);

        std::vector<const u1*>* v_EncodedData=new std::vector<const u1*>;
        std::vector<int>* v_EncodedSize=new std::vector<int>;
        int EncodeSize = GetEncoded(df,dh,v_EncodedData,v_EncodedSize);

        std::vector<const u1*>* v_ClassData=new std::vector<const u1*>;
        std::vector<int>* v_ClassDataSize=new std::vector<int>;
        int ClassDtataSize= GetClassData(pDvmDex,loader,df,dh,v_ClassData,v_ClassDataSize);

		//-------------------------------------------------------------------------------WriteFile
		ByteStream* bs = bsalloc(20000);
	    int offset = 0;
        if (bs == NULL) return;

        BuildHeader(bs,offset,dh);

        bssave(bs,filename);
        bsfree(bs);
        LOG(WARNING) << "UCHIHALART  unpack: "<<filename;
     */
	}

/*
	void BuildHeader(ByteStream* bs, int offset,const DexFile::Header& dh){
		dxb_header(bs,dh,offset);
	}

	void dxb_header(ByteStream *bs, const DexFile::Header& header,uint32_t offset)
	{
		if (bs == NULL)
		{
			return;
		}
		
		size_t data_size = sizeof(DexFile::Header);
		uint8_t* ptr = (uint8_t*) &header;

		bsseek(bs,offset);
		bswrite(bs,ptr,data_size);

	}


	int GetStrData(const art::DexFile* df,const DexFile::Header& dh,std::vector<const u1*>* v_StrData, std::vector<int>* v_StrDataLength){
		LOG(WARNING) << "UCHIHALART----------------------Get StrData";
		int StrDataSize = 0;
		unsigned int i = 0;
	    for (i = 0; i < dh.string_ids_size_; i++)
		{
			const DexFile::StringId& dsi = df->GetStringId(i);
			const u1* ptr = (const u1*)df->Begin() + dsi.string_data_off_;
			v_StrData->push_back(ptr);
		}

		for(i=0;i<v_StrData->size();i++){
			int size = read_strdata_length(v_StrData->at(i));
			v_StrDataLength->push_back(size);
			StrDataSize = StrDataSize+size;
		}

		LOG(WARNING) << "UCHIHALART----STR totalsize: "<<StrDataSize;
		return StrDataSize;

    }



	int GetTypeList(const DexFile* df,const DexFile::Header& dh,std::vector<const u1*>* v_TypelistData,std::vector<int>* v_TypelistSize){
		LOG(WARNING) << "UCHIHALART----------------------Get TypeList";
	    int TypelistSize = 0;
		unsigned int i = 0;

		for(i = 0;i<dh.proto_ids_size_;i++){
			const DexFile::ProtoId& dpi = df->GetProtoId(i);
			const u1* addr = (const u1*)df->Begin() + dpi.parameters_off_;
			int lock = 1;
			for(unsigned int j=0;j<v_TypelistData->size();j++){
				if(v_TypelistData->at(j)==addr){
					lock = 0;
				}
			}
			if(dpi.parameters_off_!=0){
				if(lock==1){
					v_TypelistData->push_back(addr);
				}
			} 			
			
		}

		for(i=0;i<dh.class_defs_size_;i++){
			const DexFile::ClassDef& dcd = df->GetClassDef(i);
			const u1* addr = (const u1*)df->Begin()+dcd.interfaces_off_;
			int lock = 1;
			for(unsigned int j=0;j<v_TypelistData->size();j++){
				if(v_TypelistData->at(j)==addr){
					lock = 0;
				}
			}
			if(dcd.interfaces_off_!=0){
				if(lock==1){
					v_TypelistData->push_back(addr);
				}
			}  			
			
		}


		for(i=0;i<v_TypelistData->size();i++){
			int size =  read_typelist_length(v_TypelistData->at(i));
			v_TypelistSize->push_back(size);
			TypelistSize=TypelistSize+size;
		}

		LOG(WARNING) << "UCHIHALART----TypeListtotalSize: "<<TypelistSize;
		return TypelistSize;

	}

	int GetEncoded(const DexFile* df,const DexFile::Header& dh,std::vector<const u1*>* v_EncodedData,std::vector<int>* v_EncodedSize){
		LOG(WARNING) << "UCHIHALART----------------------Get Encoded";
		int EncodeSize = 0;
	    unsigned int i = 0;
		for(i=0;i<dh.class_defs_size_;i++){
			const DexFile::ClassDef& dcd = df->GetClassDef(i);
			const u1* addr = (const u1*)df->Begin() + dcd.static_values_off_;
			int lock = 1;
			for(unsigned int j=0;j<v_EncodedData->size();j++){
				if(v_EncodedData->at(j)==addr){
					lock = 0;
				}
			}
			if(dcd.static_values_off_!=0){
				if(lock==1){
					v_EncodedData->push_back(addr);
				}
			}			
			
		}   

		for(i=0;i<v_EncodedData->size();i++){
			int size = read_encodedarray_length(v_EncodedData->at(i));
			v_EncodedSize->push_back(size);
			EncodeSize=EncodeSize+size;
		}


		LOG(WARNING) << "UCHIHALART----EncodedtotalSize: "<<EncodeSize;
		return EncodeSize;
	}

	int GetClassData(const DexFile* df,const DexFile::Header *dh,std::vector<const u1*>* v_ClassData,std::vector<int>* v_ClassDataSize){
		LOG(WARNING) << "UCHIHALART----------------------Get ClassData";
	    int ClassDtataSize=0;
	    unsigned int i = 0;
		for(i=0;i<dh.class_defs_size_;i++){
			const DexFile::ClassDef& dcd = df->GetClassDef(i);

			const u1* addr = (const u1*)df->Begin() + dcd.class_data_off_;
			int lock = 1;
			for(unsigned int j=0;j<v_ClassData->size();j++){
				if(v_ClassData->at(j)==addr){
					lock = 0;
				}
			}
			if(dcd.class_data_off_!=0){
				if(lock==1){
					v_ClassData->push_back(addr);
				}
			}else{
				//classDataOff=0
			};  			
			
		}

		
		for(i=0;i<v_ClassData->size();i++){
			int size = read_classdata_length(v_ClassData->at(i));
			v_ClassDataSize->push_back(size);
			ClassDtataSize =ClassDtataSize+size;
		}

        LOG(WARNING) << "UCHIHALART----ClassDatatotalSize: "<<ClassDtataSize;
		return ClassDtataSize;
	}



	int read_strdata_length(const u1* str){
		int length = 0;
  		while(true){
             if(str[length]==0x00){
             	return length+1;
             }
             length++;
  		}
	}

	int read_typelist_length(const u1* tyl){
		const DexFile::TypeList* dtl = (const DexFile::TypeList*)tyl;
		int length = 0;
    	if(dtl->Size()%2){//fill for 4 bytes
    		length = (dtl->Size()+1)*2+4;
    	}else{
    		length = dtl->Size()*2+4;
    	}
        return length;
	}

	int read_encodedarray_length(const u1* ea){
		
		int length = 0;
		const u1* start = ea;
		int number = art::DecodeUnsignedLeb128(&ea);
		//GOSSIP("EncodedNumber: %d", number);
		const u1* end = ea;
		
		//int size = (((int)ea[0]) - ((int)ea[0])%32)/32 + 1;
		int i=0;
		
		while(true){
			if(i==number){
				break;
			}
			int value = (int)ea[length];  //1 byte for value type,first 3bits is type,last 5 bits is (size-1)
			int type = value%32;// the type is high 3 bits
			int size=0;

			if(type==31||type==30){//when the type is NULL or BOOLEAN , the value size is 0
				size = 0;
			}
			else if(type==29||type ==28){
				LOG(WARNING) << "UCHIHALART----EncodedArray:Static Value May Have ERROR!!!!!!!!!!!!!";
				size = 0;
			}
			else{
				size = (value - value%32)/32 +1;  // the value size is low 5 bits
			}

			//GOSSIP("EncodedSize: %d", size);
			//GOSSIP("EncodedType: %d", type);

			length = length + size + 1;
			i++;


		}
		length = length+end-start;

        return length;
	}

	int read_classdata_length(const u1* cd){
		const u1* start = cd;
		DexClassDataHeader *pHeader = new DexClassDataHeader;
		dexReadClassDataHeader(&cd, pHeader); 


		int number = 2*(pHeader->staticFieldsSize+pHeader->instanceFieldsSize)+3*(pHeader->directMethodsSize+pHeader->virtualMethodsSize);
		for(int i=0;i<number;i++){
			readUnsignedLeb128(&cd);
			//GOSSIP("Leb128----: %d", a);
	    }
	    const u1* end = cd;
	    int length = (int)(end-start);
	    //GOSSIP("Leb128----addr: %d", length);
	    int methodNum = pHeader->directMethodsSize+pHeader->virtualMethodsSize;
		//delete pHeader;
	    return length+4*methodNum+4;  //!!!!!!!!!!!!  1 classdata may have more than 1 codeoff which will be changed.
	}
	*/

}