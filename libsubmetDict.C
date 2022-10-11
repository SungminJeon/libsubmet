// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME libsubmetDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "SPulse.h"
#include "SEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_SPulse(void *p = 0);
   static void *newArray_SPulse(Long_t size, void *p);
   static void delete_SPulse(void *p);
   static void deleteArray_SPulse(void *p);
   static void destruct_SPulse(void *p);
   static void streamer_SPulse(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SPulse*)
   {
      ::SPulse *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SPulse >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SPulse", ::SPulse::Class_Version(), "SPulse.h", 8,
                  typeid(::SPulse), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SPulse::Dictionary, isa_proxy, 16,
                  sizeof(::SPulse) );
      instance.SetNew(&new_SPulse);
      instance.SetNewArray(&newArray_SPulse);
      instance.SetDelete(&delete_SPulse);
      instance.SetDeleteArray(&deleteArray_SPulse);
      instance.SetDestructor(&destruct_SPulse);
      instance.SetStreamerFunc(&streamer_SPulse);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SPulse*)
   {
      return GenerateInitInstanceLocal((::SPulse*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SPulse*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SEvent(void *p = 0);
   static void *newArray_SEvent(Long_t size, void *p);
   static void delete_SEvent(void *p);
   static void deleteArray_SEvent(void *p);
   static void destruct_SEvent(void *p);
   static void streamer_SEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SEvent*)
   {
      ::SEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("SEvent", ::SEvent::Class_Version(), "SEvent.h", 10,
                  typeid(::SEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SEvent::Dictionary, isa_proxy, 16,
                  sizeof(::SEvent) );
      instance.SetNew(&new_SEvent);
      instance.SetNewArray(&newArray_SEvent);
      instance.SetDelete(&delete_SEvent);
      instance.SetDeleteArray(&deleteArray_SEvent);
      instance.SetDestructor(&destruct_SEvent);
      instance.SetStreamerFunc(&streamer_SEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SEvent*)
   {
      return GenerateInitInstanceLocal((::SEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::SEvent*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr SPulse::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SPulse::Class_Name()
{
   return "SPulse";
}

//______________________________________________________________________________
const char *SPulse::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SPulse*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SPulse::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SPulse*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SPulse::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SPulse*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SPulse::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SPulse*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *SEvent::Class_Name()
{
   return "SEvent";
}

//______________________________________________________________________________
const char *SEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int SEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void SPulse::Streamer(TBuffer &R__b)
{
   // Stream an object of class SPulse.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> md_Mean;
      R__b >> md_Var;
      R__b >> md_Skew;
      R__b >> md_Kurt;
      R__b >> md_Threshold;
      R__b >> md_PedMean;
      R__b >> md_Height;
      R__b >> mi_N;
      R__b >> mf_PeakTime;
      R__b >> md_MeanTime;
      {
         vector<float> &R__stl =  mv_Volts;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  mv_Times;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b.CheckByteCount(R__s, R__c, SPulse::IsA());
   } else {
      R__c = R__b.WriteVersion(SPulse::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << md_Mean;
      R__b << md_Var;
      R__b << md_Skew;
      R__b << md_Kurt;
      R__b << md_Threshold;
      R__b << md_PedMean;
      R__b << md_Height;
      R__b << mi_N;
      R__b << mf_PeakTime;
      R__b << md_MeanTime;
      {
         vector<float> &R__stl =  mv_Volts;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  mv_Times;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SPulse(void *p) {
      return  p ? new(p) ::SPulse : new ::SPulse;
   }
   static void *newArray_SPulse(Long_t nElements, void *p) {
      return p ? new(p) ::SPulse[nElements] : new ::SPulse[nElements];
   }
   // Wrapper around operator delete
   static void delete_SPulse(void *p) {
      delete ((::SPulse*)p);
   }
   static void deleteArray_SPulse(void *p) {
      delete [] ((::SPulse*)p);
   }
   static void destruct_SPulse(void *p) {
      typedef ::SPulse current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SPulse(TBuffer &buf, void *obj) {
      ((::SPulse*)obj)->::SPulse::Streamer(buf);
   }
} // end of namespace ROOT for class ::SPulse

//______________________________________________________________________________
void SEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class SEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> md_Mean;
      R__b >> md_Var;
      R__b >> md_Skew;
      R__b >> md_Kurt;
      R__b >> mi_N;
      R__b >> md_Threshold;
      R__b >> mb_SelfSup;
      {
         vector<float> &R__stl =  mv_Volts;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<float> &R__stl =  mv_Times;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            float R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b >> mi_NoP;
      R__b >> mf_RoiStart;
      R__b >> mf_RoiEnd;
      mv_Ps->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, SEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(SEvent::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << md_Mean;
      R__b << md_Var;
      R__b << md_Skew;
      R__b << md_Kurt;
      R__b << mi_N;
      R__b << md_Threshold;
      R__b << mb_SelfSup;
      {
         vector<float> &R__stl =  mv_Volts;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<float> &R__stl =  mv_Times;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<float>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << mi_NoP;
      R__b << mf_RoiStart;
      R__b << mf_RoiEnd;
      mv_Ps->Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SEvent(void *p) {
      return  p ? new(p) ::SEvent : new ::SEvent;
   }
   static void *newArray_SEvent(Long_t nElements, void *p) {
      return p ? new(p) ::SEvent[nElements] : new ::SEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_SEvent(void *p) {
      delete ((::SEvent*)p);
   }
   static void deleteArray_SEvent(void *p) {
      delete [] ((::SEvent*)p);
   }
   static void destruct_SEvent(void *p) {
      typedef ::SEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_SEvent(TBuffer &buf, void *obj) {
      ((::SEvent*)obj)->::SEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::SEvent

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 386,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      ::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace {
  void TriggerDictionaryInitialization_libsubmetDict_Impl() {
    static const char* headers[] = {
"SPulse.h",
"SEvent.h",
0
    };
    static const char* includePaths[] = {
"/opt/root/root-6.24.06/include/",
"/data/libsubmet/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libsubmetDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$SPulse.h")))  SPulse;
class __attribute__((annotate("$clingAutoload$SEvent.h")))  SEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libsubmetDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "SPulse.h"
#include "SEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"SEvent", payloadCode, "@",
"SPulse", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libsubmetDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libsubmetDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libsubmetDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libsubmetDict() {
  TriggerDictionaryInitialization_libsubmetDict_Impl();
}
