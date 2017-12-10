namespace wf {
    template <typename T>
    class SharedPointer {
    private:
        T * ptr;
        int * counter;
    public:
        SharedPointer();
        SharedPointer(T * p);
        SharedPointer(SharedPointer sp);
        ~SharedPointer();
        SharedPointer& operator=(const SharedPointer &sp);
        T& operator*();
    };
}
