#ifndef GLWRAPPER_DETAIL_RESOURCE_HPP
#define GLWRAPPER_DETAIL_RESOURCE_HPP

namespace glwrapper {

namespace detail {

    template <typename T>
    struct ResourceTraits;
    /*
        using Handle = ...
        static void destroy(Handle)
    */

    /*
    A deletable OpenGL resource.
    E.g.: shader, buffer, program.

    ResourceTraits<T> must be specialized.
    ResourceTraits::Handle will usually by a pointer or integral type.
    ResourceTraits::destroy() will be called upon deletion, if handle is not the default value.

    moveable, non-copyable
    */
    template <typename T>
    class Resource {
    private:
        using Traits = ResourceTraits<T>;

    public:
        using Handle = typename Traits::Handle;
        
    private:
        Handle handle;

    public:

        Resource(Handle handle = Handle{})
            : handle(handle) {
        }

        Resource(const Resource& source) = delete;

        Resource(Resource&& source)
            : handle(source.handle) {
            source.handle = Handle{};
        }

        Resource& operator=(const Resource& source) = delete;

        Resource& operator=(Resource&& source) {
            handle = source.handle;
            source.handle = Handle{};
            return *this;
        }
        
        ~Resource() {
            if(handle != Handle{}) {
                Traits::destroy(handle);
            }
        }

        Handle getHandle() const {
            return handle;
        }

        void setHandle(Handle handle) {
            this->handle = handle;
        }
    };

} // namespace detail

} // namespace glwrapper

#endif // #ifndef GLWRAPPER_DETAIL_RESOURCE_HPP
