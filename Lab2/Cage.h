
namespace gol {
    class Cage {
    private:
        char state;
    public:
        Cage(char state);
        char get_state(); // . - empty, * - live
        void set_state(char st);
    };
}