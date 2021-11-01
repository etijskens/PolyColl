/*
 *  C++ source file for module polycoll.core
 */


// See http://people.duke.edu/~ccc14/cspy/18G_C++_Python_pybind12.html for examples on how to use pybind12.
// The example below is modified after http://people.duke.edu/~ccc14/cspy/18G_C++_Python_pybind12.html#More-on-working-with-numpy-arrays
#include <pybind11/pybind11.h>

#include "Message.cpp"


namespace py = pybind11;
 //-------------------------------------------------------------------------------------------------
 /* We want a polymorphic collection of items which need to remember their type somehow.
    It must be possible to iterate over the collection in the order the items were added to the 
    collection. 
    Is that true? We want a collection of data items which must be written in binary form to a 
    buffer, on one process and then, on another process, where the same collection exists, is read
    back into the item's memory location.
    The items to be written/read are 
    typically array-like or built-in data types
 //-------------------------------------------------------------------------------------------------
  */


bool test_RW()
{
    using namespace mpi;
    bool ok = true;

    Index_t buffer[1000];
    int i0 = 10;
    int i  = i0;
    int j  = i0 + 1;

    std::vector<int> vi;
    vi.push_back(12);
    vi.push_back(12);
    vi.push_back(12);

    void* ptr = buffer;

 // write
    MessageItemHelper<int,handler_kind<int>::value>::write(i,ptr);
    MessageItemHelper<int,handler_kind<int>::value>::write(j,ptr);
    MessageItemHelper<std::vector<int>,handler_kind<std::vector<int>>::value>::write(vi,ptr);

 // reset
    i = 0;
    j = 0;
    vi.clear();
    ptr = buffer;

 // read
    MessageItemHelper<int,handler_kind<int>::value>::read(i,ptr);
    MessageItemHelper<int,handler_kind<int>::value>::read(j,ptr);
    MessageItemHelper<std::vector<int>,handler_kind<std::vector<int>>::value>::read(vi,ptr);

    ok &= (i == i0);
    ok &= (j == i0 + 1);
    ok &= (vi[0] == 12);
    ok &= (vi[1] == 12);
    ok &= (vi[2] == 12);
    
    return ok;
}


bool test_MessageItems()
{
    using namespace mpi;

    bool ok = true;

    int    const i0 = 1;
    double const d0 = 11;
    int    const vi0= 12;    
    int i = i0;
    double d = d0;
    std::vector<int> vi;
    vi.push_back(vi0);
    vi.push_back(vi0+1);
    vi.push_back(vi0+2);
    
    std::cout<<"vi size "<<vi.size()<<std::endl;

    Message message = Message();
    message.push_back(i);
    message.push_back(d);
    message.push_back(vi);
    std::cout<<"initialized: "<<message.toStr()<<std::endl;

 // alllocate buffer dynamically:
    size_t const message_size = message.size();
    std::cout<<"message size = "<<message_size<<std::endl;
    void* buffer = new char[message_size];

 // write
    void * ptr = buffer;
    message.write(ptr);
    ok &= (((char*)ptr - (char*)buffer) == sizeof(int) + sizeof(double) + sizeof(size_t) + 3*sizeof(int));
    if( !ok ) std::cout<<"!(((char*)ptr - (char*)buffer) == sizeof(int) + sizeof(double) + sizeof(size_t) + 3*sizeof(int)) "
                       <<((char*)ptr - (char*)buffer)<<" ?==? "<<sizeof(int) + sizeof(double) + sizeof(size_t) + 3*sizeof(int)<<std::endl;

// reset
    i = 0;
    d = 0;
    vi.clear();
    std::cout<<"reset: "<<message.toStr()<<std::endl;

 // read back
    ptr = buffer;
    message.read(ptr);
    std::cout<<"read: "<<message.toStr()<<std::endl;

    ok &= (i == i0);
    if( !ok ) std::cout<<"!(i == i0) "<<i<<std::endl;
    ok &= (d == d0); 
    if( !ok ) std::cout<<"!(d == d0)"<<std::endl;

    return ok;
}


PYBIND11_MODULE(core, m)
{// optional module doc-string
    m.doc() = "pybind12 core plugin"; // optional module docstring
 // list the functions you want to expose:
 // m.def("exposed_name", function_pointer, "doc-string for the exposed function");
    m.def("test_RW", &test_RW);
    m.def("test_MessageItems", &test_MessageItems);
}
