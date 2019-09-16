// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME G__KFParticle

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

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleBase.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticle.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFVertex.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPartEfficiencies.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCParticle.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticleTest/KFParticleTest.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_KFParticleBase(void *p);
   static void deleteArray_KFParticleBase(void *p);
   static void destruct_KFParticleBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KFParticleBase*)
   {
      ::KFParticleBase *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KFParticleBase >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KFParticleBase", ::KFParticleBase::Class_Version(), "KFParticleBase.h", 43,
                  typeid(::KFParticleBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KFParticleBase::Dictionary, isa_proxy, 4,
                  sizeof(::KFParticleBase) );
      instance.SetDelete(&delete_KFParticleBase);
      instance.SetDeleteArray(&deleteArray_KFParticleBase);
      instance.SetDestructor(&destruct_KFParticleBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KFParticleBase*)
   {
      return GenerateInitInstanceLocal((::KFParticleBase*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KFParticleBase*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KFParticle(void *p = 0);
   static void *newArray_KFParticle(Long_t size, void *p);
   static void delete_KFParticle(void *p);
   static void deleteArray_KFParticle(void *p);
   static void destruct_KFParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KFParticle*)
   {
      ::KFParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KFParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KFParticle", ::KFParticle::Class_Version(), "KFParticle.h", 47,
                  typeid(::KFParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KFParticle::Dictionary, isa_proxy, 4,
                  sizeof(::KFParticle) );
      instance.SetNew(&new_KFParticle);
      instance.SetNewArray(&newArray_KFParticle);
      instance.SetDelete(&delete_KFParticle);
      instance.SetDeleteArray(&deleteArray_KFParticle);
      instance.SetDestructor(&destruct_KFParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KFParticle*)
   {
      return GenerateInitInstanceLocal((::KFParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KFParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KFVertex(void *p = 0);
   static void *newArray_KFVertex(Long_t size, void *p);
   static void delete_KFVertex(void *p);
   static void deleteArray_KFVertex(void *p);
   static void destruct_KFVertex(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KFVertex*)
   {
      ::KFVertex *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KFVertex >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KFVertex", ::KFVertex::Class_Version(), "KFVertex.h", 29,
                  typeid(::KFVertex), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KFVertex::Dictionary, isa_proxy, 4,
                  sizeof(::KFVertex) );
      instance.SetNew(&new_KFVertex);
      instance.SetNewArray(&newArray_KFVertex);
      instance.SetDelete(&delete_KFVertex);
      instance.SetDeleteArray(&deleteArray_KFVertex);
      instance.SetDestructor(&destruct_KFVertex);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KFVertex*)
   {
      return GenerateInitInstanceLocal((::KFVertex*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KFVertex*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KFPartEfficiencies(void *p = 0);
   static void *newArray_KFPartEfficiencies(Long_t size, void *p);
   static void delete_KFPartEfficiencies(void *p);
   static void deleteArray_KFPartEfficiencies(void *p);
   static void destruct_KFPartEfficiencies(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KFPartEfficiencies*)
   {
      ::KFPartEfficiencies *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KFPartEfficiencies >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KFPartEfficiencies", ::KFPartEfficiencies::Class_Version(), "KFPartEfficiencies.h", 83,
                  typeid(::KFPartEfficiencies), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KFPartEfficiencies::Dictionary, isa_proxy, 4,
                  sizeof(::KFPartEfficiencies) );
      instance.SetNew(&new_KFPartEfficiencies);
      instance.SetNewArray(&newArray_KFPartEfficiencies);
      instance.SetDelete(&delete_KFPartEfficiencies);
      instance.SetDeleteArray(&deleteArray_KFPartEfficiencies);
      instance.SetDestructor(&destruct_KFPartEfficiencies);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KFPartEfficiencies*)
   {
      return GenerateInitInstanceLocal((::KFPartEfficiencies*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KFPartEfficiencies*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KFMCParticle(void *p = 0);
   static void *newArray_KFMCParticle(Long_t size, void *p);
   static void delete_KFMCParticle(void *p);
   static void deleteArray_KFMCParticle(void *p);
   static void destruct_KFMCParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KFMCParticle*)
   {
      ::KFMCParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KFMCParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KFMCParticle", ::KFMCParticle::Class_Version(), "KFMCParticle.h", 38,
                  typeid(::KFMCParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KFMCParticle::Dictionary, isa_proxy, 4,
                  sizeof(::KFMCParticle) );
      instance.SetNew(&new_KFMCParticle);
      instance.SetNewArray(&newArray_KFMCParticle);
      instance.SetDelete(&delete_KFMCParticle);
      instance.SetDeleteArray(&deleteArray_KFMCParticle);
      instance.SetDestructor(&destruct_KFMCParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KFMCParticle*)
   {
      return GenerateInitInstanceLocal((::KFMCParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KFMCParticle*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_KFParticleTest(void *p = 0);
   static void *newArray_KFParticleTest(Long_t size, void *p);
   static void delete_KFParticleTest(void *p);
   static void deleteArray_KFParticleTest(void *p);
   static void destruct_KFParticleTest(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::KFParticleTest*)
   {
      ::KFParticleTest *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::KFParticleTest >(0);
      static ::ROOT::TGenericClassInfo 
         instance("KFParticleTest", ::KFParticleTest::Class_Version(), "KFParticleTest/KFParticleTest.h", 24,
                  typeid(::KFParticleTest), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::KFParticleTest::Dictionary, isa_proxy, 4,
                  sizeof(::KFParticleTest) );
      instance.SetNew(&new_KFParticleTest);
      instance.SetNewArray(&newArray_KFParticleTest);
      instance.SetDelete(&delete_KFParticleTest);
      instance.SetDeleteArray(&deleteArray_KFParticleTest);
      instance.SetDestructor(&destruct_KFParticleTest);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::KFParticleTest*)
   {
      return GenerateInitInstanceLocal((::KFParticleTest*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::KFParticleTest*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr KFParticleBase::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KFParticleBase::Class_Name()
{
   return "KFParticleBase";
}

//______________________________________________________________________________
const char *KFParticleBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFParticleBase*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KFParticleBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFParticleBase*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KFParticleBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFParticleBase*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KFParticleBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFParticleBase*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KFParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KFParticle::Class_Name()
{
   return "KFParticle";
}

//______________________________________________________________________________
const char *KFParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KFParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KFParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KFParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KFVertex::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KFVertex::Class_Name()
{
   return "KFVertex";
}

//______________________________________________________________________________
const char *KFVertex::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFVertex*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KFVertex::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFVertex*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KFVertex::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFVertex*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KFVertex::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFVertex*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KFPartEfficiencies::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KFPartEfficiencies::Class_Name()
{
   return "KFPartEfficiencies";
}

//______________________________________________________________________________
const char *KFPartEfficiencies::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFPartEfficiencies*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KFPartEfficiencies::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFPartEfficiencies*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KFPartEfficiencies::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFPartEfficiencies*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KFPartEfficiencies::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFPartEfficiencies*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KFMCParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KFMCParticle::Class_Name()
{
   return "KFMCParticle";
}

//______________________________________________________________________________
const char *KFMCParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFMCParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KFMCParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFMCParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KFMCParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFMCParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KFMCParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFMCParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr KFParticleTest::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *KFParticleTest::Class_Name()
{
   return "KFParticleTest";
}

//______________________________________________________________________________
const char *KFParticleTest::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFParticleTest*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int KFParticleTest::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::KFParticleTest*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *KFParticleTest::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFParticleTest*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *KFParticleTest::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::KFParticleTest*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void KFParticleBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class KFParticleBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KFParticleBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(KFParticleBase::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_KFParticleBase(void *p) {
      delete ((::KFParticleBase*)p);
   }
   static void deleteArray_KFParticleBase(void *p) {
      delete [] ((::KFParticleBase*)p);
   }
   static void destruct_KFParticleBase(void *p) {
      typedef ::KFParticleBase current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KFParticleBase

//______________________________________________________________________________
void KFParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class KFParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KFParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(KFParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KFParticle(void *p) {
      return  p ? new(p) ::KFParticle : new ::KFParticle;
   }
   static void *newArray_KFParticle(Long_t nElements, void *p) {
      return p ? new(p) ::KFParticle[nElements] : new ::KFParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_KFParticle(void *p) {
      delete ((::KFParticle*)p);
   }
   static void deleteArray_KFParticle(void *p) {
      delete [] ((::KFParticle*)p);
   }
   static void destruct_KFParticle(void *p) {
      typedef ::KFParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KFParticle

//______________________________________________________________________________
void KFVertex::Streamer(TBuffer &R__b)
{
   // Stream an object of class KFVertex.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KFVertex::Class(),this);
   } else {
      R__b.WriteClassBuffer(KFVertex::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KFVertex(void *p) {
      return  p ? new(p) ::KFVertex : new ::KFVertex;
   }
   static void *newArray_KFVertex(Long_t nElements, void *p) {
      return p ? new(p) ::KFVertex[nElements] : new ::KFVertex[nElements];
   }
   // Wrapper around operator delete
   static void delete_KFVertex(void *p) {
      delete ((::KFVertex*)p);
   }
   static void deleteArray_KFVertex(void *p) {
      delete [] ((::KFVertex*)p);
   }
   static void destruct_KFVertex(void *p) {
      typedef ::KFVertex current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KFVertex

//______________________________________________________________________________
void KFPartEfficiencies::Streamer(TBuffer &R__b)
{
   // Stream an object of class KFPartEfficiencies.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KFPartEfficiencies::Class(),this);
   } else {
      R__b.WriteClassBuffer(KFPartEfficiencies::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KFPartEfficiencies(void *p) {
      return  p ? new(p) ::KFPartEfficiencies : new ::KFPartEfficiencies;
   }
   static void *newArray_KFPartEfficiencies(Long_t nElements, void *p) {
      return p ? new(p) ::KFPartEfficiencies[nElements] : new ::KFPartEfficiencies[nElements];
   }
   // Wrapper around operator delete
   static void delete_KFPartEfficiencies(void *p) {
      delete ((::KFPartEfficiencies*)p);
   }
   static void deleteArray_KFPartEfficiencies(void *p) {
      delete [] ((::KFPartEfficiencies*)p);
   }
   static void destruct_KFPartEfficiencies(void *p) {
      typedef ::KFPartEfficiencies current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KFPartEfficiencies

//______________________________________________________________________________
void KFMCParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class KFMCParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KFMCParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(KFMCParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KFMCParticle(void *p) {
      return  p ? new(p) ::KFMCParticle : new ::KFMCParticle;
   }
   static void *newArray_KFMCParticle(Long_t nElements, void *p) {
      return p ? new(p) ::KFMCParticle[nElements] : new ::KFMCParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_KFMCParticle(void *p) {
      delete ((::KFMCParticle*)p);
   }
   static void deleteArray_KFMCParticle(void *p) {
      delete [] ((::KFMCParticle*)p);
   }
   static void destruct_KFMCParticle(void *p) {
      typedef ::KFMCParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KFMCParticle

//______________________________________________________________________________
void KFParticleTest::Streamer(TBuffer &R__b)
{
   // Stream an object of class KFParticleTest.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(KFParticleTest::Class(),this);
   } else {
      R__b.WriteClassBuffer(KFParticleTest::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_KFParticleTest(void *p) {
      return  p ? new(p) ::KFParticleTest : new ::KFParticleTest;
   }
   static void *newArray_KFParticleTest(Long_t nElements, void *p) {
      return p ? new(p) ::KFParticleTest[nElements] : new ::KFParticleTest[nElements];
   }
   // Wrapper around operator delete
   static void delete_KFParticleTest(void *p) {
      delete ((::KFParticleTest*)p);
   }
   static void deleteArray_KFParticleTest(void *p) {
      delete [] ((::KFParticleTest*)p);
   }
   static void destruct_KFParticleTest(void *p) {
      typedef ::KFParticleTest current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::KFParticleTest

namespace ROOT {
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary();
   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEintgRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEintgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p);
   static void destruct_vectorlEvectorlEintgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<int> >*)
   {
      vector<vector<int> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<int> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<int> >", -2, "vector", 214,
                  typeid(vector<vector<int> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEintgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<int> >) );
      instance.SetNew(&new_vectorlEvectorlEintgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEintgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEintgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEintgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEintgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<int> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<vector<int> >*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEintgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<int> >*)0x0)->GetClass();
      vectorlEvectorlEintgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEintgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEintgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<int> > : new vector<vector<int> >;
   }
   static void *newArray_vectorlEvectorlEintgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<int> >[nElements] : new vector<vector<int> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEintgRsPgR(void *p) {
      delete ((vector<vector<int> >*)p);
   }
   static void deleteArray_vectorlEvectorlEintgRsPgR(void *p) {
      delete [] ((vector<vector<int> >*)p);
   }
   static void destruct_vectorlEvectorlEintgRsPgR(void *p) {
      typedef vector<vector<int> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<int> >

namespace ROOT {
   static TClass *vectorlEstringgR_Dictionary();
   static void vectorlEstringgR_TClassManip(TClass*);
   static void *new_vectorlEstringgR(void *p = 0);
   static void *newArray_vectorlEstringgR(Long_t size, void *p);
   static void delete_vectorlEstringgR(void *p);
   static void deleteArray_vectorlEstringgR(void *p);
   static void destruct_vectorlEstringgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<string>*)
   {
      vector<string> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<string>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<string>", -2, "vector", 214,
                  typeid(vector<string>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEstringgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<string>) );
      instance.SetNew(&new_vectorlEstringgR);
      instance.SetNewArray(&newArray_vectorlEstringgR);
      instance.SetDelete(&delete_vectorlEstringgR);
      instance.SetDeleteArray(&deleteArray_vectorlEstringgR);
      instance.SetDestructor(&destruct_vectorlEstringgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<string> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<string>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEstringgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<string>*)0x0)->GetClass();
      vectorlEstringgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEstringgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEstringgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string> : new vector<string>;
   }
   static void *newArray_vectorlEstringgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<string>[nElements] : new vector<string>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEstringgR(void *p) {
      delete ((vector<string>*)p);
   }
   static void deleteArray_vectorlEstringgR(void *p) {
      delete [] ((vector<string>*)p);
   }
   static void destruct_vectorlEstringgR(void *p) {
      typedef vector<string> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<string>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 214,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *maplEstringcOintgR_Dictionary();
   static void maplEstringcOintgR_TClassManip(TClass*);
   static void *new_maplEstringcOintgR(void *p = 0);
   static void *newArray_maplEstringcOintgR(Long_t size, void *p);
   static void delete_maplEstringcOintgR(void *p);
   static void deleteArray_maplEstringcOintgR(void *p);
   static void destruct_maplEstringcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,int>*)
   {
      map<string,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,int>", -2, "map", 96,
                  typeid(map<string,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,int>) );
      instance.SetNew(&new_maplEstringcOintgR);
      instance.SetNewArray(&newArray_maplEstringcOintgR);
      instance.SetDelete(&delete_maplEstringcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOintgR);
      instance.SetDestructor(&destruct_maplEstringcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<string,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,int>*)0x0)->GetClass();
      maplEstringcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int> : new map<string,int>;
   }
   static void *newArray_maplEstringcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,int>[nElements] : new map<string,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOintgR(void *p) {
      delete ((map<string,int>*)p);
   }
   static void deleteArray_maplEstringcOintgR(void *p) {
      delete [] ((map<string,int>*)p);
   }
   static void destruct_maplEstringcOintgR(void *p) {
      typedef map<string,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,int>

namespace ROOT {
   static TClass *maplEintcOintgR_Dictionary();
   static void maplEintcOintgR_TClassManip(TClass*);
   static void *new_maplEintcOintgR(void *p = 0);
   static void *newArray_maplEintcOintgR(Long_t size, void *p);
   static void delete_maplEintcOintgR(void *p);
   static void deleteArray_maplEintcOintgR(void *p);
   static void destruct_maplEintcOintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,int>*)
   {
      map<int,int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,int>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,int>", -2, "map", 96,
                  typeid(map<int,int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOintgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,int>) );
      instance.SetNew(&new_maplEintcOintgR);
      instance.SetNewArray(&newArray_maplEintcOintgR);
      instance.SetDelete(&delete_maplEintcOintgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOintgR);
      instance.SetDestructor(&destruct_maplEintcOintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const map<int,int>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,int>*)0x0)->GetClass();
      maplEintcOintgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int> : new map<int,int>;
   }
   static void *newArray_maplEintcOintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,int>[nElements] : new map<int,int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOintgR(void *p) {
      delete ((map<int,int>*)p);
   }
   static void deleteArray_maplEintcOintgR(void *p) {
      delete [] ((map<int,int>*)p);
   }
   static void destruct_maplEintcOintgR(void *p) {
      typedef map<int,int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,int>

namespace {
  void TriggerDictionaryInitialization_libKFParticle_Impl() {
    static const char* headers[] = {
"/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleBase.h",
"/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticle.h",
"/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFVertex.h",
"/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPartEfficiencies.h",
"/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCParticle.h",
"/home/user/cbmdir/kfpf/KFParticle/KFParticleTest/KFParticleTest.h",
0
    };
    static const char* includePaths[] = {
"/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance",
"/home/user/cbmdir/kfpf/KFParticle/KFParticle",
"/home/user/cbmdir/Vc/install/include",
"/home/user/cbmdir/kfpf/KFParticle",
"/home/user/Root6/build/include",
"/home/user/Root6/build/include",
"/home/user/cbmdir/kfpf/KFParticle/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libKFParticle dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleBase.h")))  KFParticleBase;
class __attribute__((annotate("$clingAutoload$/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticle.h")))  KFParticle;
class __attribute__((annotate("$clingAutoload$/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFVertex.h")))  KFVertex;
class __attribute__((annotate("$clingAutoload$/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPartEfficiencies.h")))  KFPartEfficiencies;
class __attribute__((annotate("$clingAutoload$/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCParticle.h")))  KFMCParticle;
class __attribute__((annotate("$clingAutoload$/home/user/cbmdir/kfpf/KFParticle/KFParticleTest/KFParticleTest.h")))  KFParticleTest;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libKFParticle dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef DO_TPCCATRACKER_EFF_PERFORMANCE
  #define DO_TPCCATRACKER_EFF_PERFORMANCE 1
#endif
#ifndef HomogeneousField
  #define HomogeneousField 1
#endif
#ifndef USE_TIMERS
  #define USE_TIMERS 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticleBase.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFParticle.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticle/KFVertex.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFPartEfficiencies.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticlePerformance/KFMCParticle.h"
#include "/home/user/cbmdir/kfpf/KFParticle/KFParticleTest/KFParticleTest.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"KFMCParticle", payloadCode, "@",
"KFPartEfficiencies", payloadCode, "@",
"KFParticle", payloadCode, "@",
"KFParticleBase", payloadCode, "@",
"KFParticleTest", payloadCode, "@",
"KFVertex", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libKFParticle",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libKFParticle_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libKFParticle_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libKFParticle() {
  TriggerDictionaryInitialization_libKFParticle_Impl();
}
