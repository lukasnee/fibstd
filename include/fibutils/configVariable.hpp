// TODO: add preconfig and postconfig void(void) optional callbacks.

template <typename T> class ConfigVariable
{
public:
    ConfigVariable(const T &value) : value(value)
    {
    }

    void set(const T &value)
    {
        this->value = value;
    }
    const T &get()
    {
        return this->value;
    }

private:
    T value;
};
