class ConstantVelocityPredictor : public Predictor
{
public:
    void init() override;

    FilterState predict(
        const FilterState& previous_state,
        double dt) override;

    void reset() override;
};