class Corrector
{
public:
    virtual ~Corrector() = default;

    virtual void init() = 0;

    virtual void correct(
        FilterState& state,
        const Measurement& measurement) = 0;

    virtual void reset() = 0;
};