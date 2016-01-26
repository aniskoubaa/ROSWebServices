   #include <iostream>
    #include <string>
    #include "serialize/json.h"

    /* A class that you want to serialize. */
    class MyClass
    {   
       public:
 	int         data1;
        float       data2;
        std::string data3;

        // This is only required if the members are private.
        friend struct ThorsAnvil::Serialize::Json::JsonSerializeTraits<MyClass>;
        
            MyClass(int a, float b, std::string const& c): data1(a), data2(b), data3(c) {}
            friend std::ostream& operator<<(std::ostream& stream, MyClass const& value)
            {   
                return stream << value.data1 << " : " << value.data2 << " : " << value.data3;
            }   

    };  

    /*
     * You can manually set up a structure that defines the traits.
     * But I was convinced that the process needs to be simplified.
     * So the following macros builds the serialization class for you.
     */  
   
    JsonSerializeTraits_MAKE(void, MyClass, data1, data2, data3);

    int main()
    {   
        MyClass     obj(56, 23.456, "Hi there");

        // Outputs the object using the stream operator
        std::cout << obj << "\n";

        // Outputs the object in json.
        // Note: No intermediate object is made it scans the object
        std::cout << ThorsAnvil::Serialize::jsonExport(obj) << "\n";

        // This reads JSON and converts it into calls that populate
        // the object. So if you type a valid json object and update it
        //
        // try typing this: =>  { "data": 2345 }
        //std::cin  >> ThorsAnvil::Serialize::jsonImport(obj);


        // Now print out the object again to prove it was changed.
        std::cout << obj << "\n";

return 0;
    }



    /*
     * The following is for documentation:
     * The above macro JsonSerializeTraits_MAKE() expands to the following code

    namespace ThorsAnvil
    {
        namespace Serialize
        {
            namespace Json
            {

    template<>
    struct JsonSerializeTraits<MyClass>
    {
        typedef MyClass             LocalType;
        typedef void                ParentType;
        static JsonSerializeType const  type    = Map;

        THORSANVIL_SERIALIZE_JsonAttribute(MyClass, data1);
        THORSANVIL_SERIALIZE_JsonAttribute(MyClass, data2);
        THORSANVIL_SERIALIZE_JsonAttribute(MyClass, data3);
        typedef boost::mpl::vector<data1, data2, data3>         SerializeInfo;
    };  

            }
        }
    }

     */


