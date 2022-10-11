// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME seventdict
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
#include "Pulse.h"
#include "SEvent.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_Pulse(void *p = 0);
   static void *newArray_Pulse(Long_t size, void *p);
   static void delete_Pulse(void *p);
   static void deleteArray_Pulse(void *p);
   static void destruct_Pulse(void *p);
   static void streamer_Pulse(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pulse*)
   {
      ::Pulse *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Pulse >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Pulse", ::Pulse::Class_Version(), "Pulse.h", 8,
                  typeid(::Pulse), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Pulse::Dictionary, isa_proxy, 16,
                  sizeof(::Pulse) );
      instance.SetNew(&new_Pulse);
      instance.SetNewArray(&newArray_Pulse);
      instance.SetDelete(&delete_Pulse);
      instance.SetDeleteArray(&deleteArray_Pulse);
      instance.SetDestructor(&destruct_Pulse);
      instance.SetStreamerFunc(&streamer_Pulse);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pulse*)
   {
      return GenerateInitInstanceLocal((::Pulse*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Pulse*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
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
         instance("SEvent", ::SEvent::Class_Version(), "SEvent.h", 13,
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
atomic_TClass_ptr Pulse::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Pulse::Class_Name()
{
   return "Pulse";
}

//______________________________________________________________________________
const char *Pulse::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Pulse*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Pulse::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Pulse*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Pulse::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Pulse*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Pulse::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Pulse*)0x0)->GetClass(); }
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
void Pulse::Streamer(TBuffer &R__b)
{
   // Stream an object of class Pulse.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> mean;
      R__b >> rms;
      R__b >> var;
      R__b >> kurt1;
      R__b >> skew1;
      R__b >> threshold;
      R__b >> pedMean;
      R__b >> Height;
      R__b >> Area;
      R__b >> N;
      R__b >> PeakTiming;
      {
         vector<double> &R__stl =  numbers;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      {
         vector<double> &R__stl =  time;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b.CheckByteCount(R__s, R__c, Pulse::IsA());
   } else {
      R__c = R__b.WriteVersion(Pulse::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << mean;
      R__b << rms;
      R__b << var;
      R__b << kurt1;
      R__b << skew1;
      R__b << threshold;
      R__b << pedMean;
      R__b << Height;
      R__b << Area;
      R__b << N;
      R__b << PeakTiming;
      {
         vector<double> &R__stl =  numbers;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<double>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      {
         vector<double> &R__stl =  time;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<double>::iterator R__k;
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
   static void *new_Pulse(void *p) {
      return  p ? new(p) ::Pulse : new ::Pulse;
   }
   static void *newArray_Pulse(Long_t nElements, void *p) {
      return p ? new(p) ::Pulse[nElements] : new ::Pulse[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pulse(void *p) {
      delete ((::Pulse*)p);
   }
   static void deleteArray_Pulse(void *p) {
      delete [] ((::Pulse*)p);
   }
   static void destruct_Pulse(void *p) {
      typedef ::Pulse current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_Pulse(TBuffer &buf, void *obj) {
      ((::Pulse*)obj)->::Pulse::Streamer(buf);
   }
} // end of namespace ROOT for class ::Pulse

//______________________________________________________________________________
void SEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class SEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> mean;
      R__b >> rms;
      R__b >> var;
      R__b >> skew1;
      R__b >> skew2;
      R__b >> skew3;
      R__b >> kurt1;
      R__b >> kurt2;
      R__b >> kurt3;
      R__b >> N;
      R__b >> entries;
      R__b >> threshold;
      {
         vector<double> &R__stl =  numbers;
         R__stl.clear();
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            R__stl.push_back(R__t);
         }
      }
      R__b >> nop;
      R__b >> sigStart;
      R__b >> sigEnd;
      PulseContainer->Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, SEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(SEvent::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << mean;
      R__b << rms;
      R__b << var;
      R__b << skew1;
      R__b << skew2;
      R__b << skew3;
      R__b << kurt1;
      R__b << kurt2;
      R__b << kurt3;
      R__b << N;
      R__b << entries;
      R__b << threshold;
      {
         vector<double> &R__stl =  numbers;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<double>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b << nop;
      R__b << sigStart;
      R__b << sigEnd;
      PulseContainer->Streamer(R__b);
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
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 386,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      ::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_seventdict_Impl() {
    static const char* headers[] = {
"Pulse.h",
"SEvent.h",
0
    };
    static const char* includePaths[] = {
"/opt/root/root-6.24.06/include/",
"/data/libsubmet/TestClassAdd/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "seventdict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
class __attribute__((annotate("$clingAutoload$Pulse.h")))  Pulse;
class __attribute__((annotate("$clingAutoload$SEvent.h")))  SEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "seventdict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "Pulse.h"
#include "SEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"Pulse", payloadCode, "@",
"SEvent", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("seventdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_seventdict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_seventdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_seventdict() {
  TriggerDictionaryInitialization_seventdict_Impl();
}
