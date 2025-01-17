//----------------------------------------------------------------------------
// Allocator for SIMDised KF Particle
// .
// @author  I.Kisel, I.Kulakov, M.Zyzak
// @version 1.0
// @since   20.08.13
// 
// 
//  -= Copyright &copy ALICE HLT and CBM L1 Groups =-
//____________________________________________________________________________

#ifndef KFPSimdAllocator_H
#define KFPSimdAllocator_H

#include <Vc/Vc>

/** @class KFPSimdAllocator
 ** @brief Allocator which is needed to allocate memory in std::vector aligned by the size of SIMD vectors.
 ** @author  M.Zyzak, I.Kisel
 ** @date 05.02.2019
 ** @version 1.0
 **/

template <class T>
class KFPSimdAllocator {
 public:
 // type definitions
  typedef T        value_type;
  typedef T*       pointer;
  typedef const T* const_pointer;
  typedef T&       reference;
  typedef const T& const_reference;
  typedef std::size_t    size_type;
  typedef std::ptrdiff_t difference_type;

  /** @class rebind
   ** @brief Rebind allocator to type U of the SIMD allocator.
   ** @author  M.Zyzak, I.Kisel
   ** @date 05.02.2019
   ** @version 1.0
   **/
  template <class U>
  struct rebind {
    typedef KFPSimdAllocator<U> other;
  };

  /** Return address of "value". */
  pointer address (reference value) const {
    return &value;
  }
  /** Return address of "value". */
  const_pointer address (const_reference value) const {
    return &value;
  }

  /* constructors and destructor
        * - nothing to do because the allocator has no state
  */
  KFPSimdAllocator() throw() { }
  KFPSimdAllocator(const KFPSimdAllocator&) throw() {  }
  template <class U>
  KFPSimdAllocator (const KFPSimdAllocator<U>&) throw() {  }
  ~KFPSimdAllocator() throw() {  }

  /** Return maximum number of elements that can be allocated. */
  size_type max_size () const throw() {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }

  /** Allocate but don't initialize num elements of type T. */
  pointer allocate (size_type num, const void* = nullptr) {
//               print message and allocate memory with global new
    pointer ret = reinterpret_cast<pointer>( /*T::*/operator new(num*sizeof(T)) );
    return ret;
  }

  /** Initialize elements of allocated storage "p" with an empty element. */
  void construct (pointer p) {
  // initialize memory with placement new
    new(p) T();
  }
  
  /** Initialize elements of allocated storage "p" with value "value". */
  void construct (pointer p, const T& value) {
    new(p) T(value);
  }

  /** Destroy elements of initialized storage "p". */
  void destroy (pointer p) {
  // destroy objects by calling their destructor
    p->~T();
  }

  /** Deallocate storage p of deleted elements. */
  void deallocate (pointer p, size_type num) {
  // print message and deallocate memory with global delete
    /*T::*/operator delete(static_cast<void*>(p), num*sizeof(T));

  }

  void *operator new(size_t size, void *ptr) { return ::operator new(size, ptr);}      ///< new operator for allocation of the SIMD-alligned dynamic memory allocation
  void *operator new[](size_t size, void *ptr) { return ::operator new(size, ptr);}    ///< new operator for allocation of the SIMD-alligned dynamic memory allocation
  void *operator new(size_t size) { return _mm_malloc(size, sizeof(Vc::float_v)); }    ///< new operator for allocation of the SIMD-alligned dynamic memory allocation
  void *operator new[](size_t size) { return _mm_malloc(size, sizeof(Vc::float_v)); }  ///< new operator for allocation of the SIMD-alligned dynamic memory allocation
  void operator delete(void *ptr, size_t) { _mm_free(ptr); }                           ///< delete operator for the SIMD-alligned dynamic memory release
  void operator delete[](void *ptr, size_t) { _mm_free(ptr); }                         ///< delete operator for the SIMD-alligned dynamic memory release
}; // KFPSimdAllocator
      
#endif //KFPSimdAllocator
