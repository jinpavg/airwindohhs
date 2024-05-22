#pragma once
#include "effect.hpp"
#include <cstdlib>

namespace airwindohhs {
template <typename T>
class Tremolo final : public Effect<T>
{
    std::string m_name{ "Tremolo" };

    uint32_t fpdL;
    uint32_t fpdR;
    // default stuff
    double sweep;
    double speedChase;
    double depthChase;
    double speedAmount;
    double depthAmount;
    double lastSpeed;
    double lastDepth;
    float A;
    float B;

    enum params
    {
        kParamA = 0,
        kParamB = 1,
        kNumParameters = 2

    };

  public:
    Tremolo()
    {
        A = 0.5;
        B = 1.0;
        sweep = 3.141592653589793238 / 2.0;
        speedChase = 0.0;
        depthChase = 0.0;
        speedAmount = 1.0;
        depthAmount = 0.0;
        lastSpeed = 1000.0;
        lastDepth = 1000.0;
        fpdL = 1.0;
        while (fpdL < 16386) {
            fpdL = rand() * UINT32_MAX;
        }
        fpdR = 1.0;
        while (fpdR < 16386) {
            fpdR = rand() * UINT32_MAX;
        }
        // this is reset: values being initialized only once. Startup values, whatever they are.
    }

    constexpr std::string_view name()
    {
        return m_name;
    }

    void set_parameter_value(int index, float value)
    {
        switch (static_cast<params>(index))
        {
            case kParamA: A = value; break;
            case kParamB: B = value; break;

            default: break;
        }
    }

    float get_parameter_value(int index)
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return A;
            case kParamB: return B;

            default: break;
        }
        return 0.0;
    }

    constexpr std::string_view get_parameter_name(int index)
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return "Speed";
            case kParamB: return "Depth";

            default: break;
        }
        return {};
    }

    std::string get_parameter_display(int index) const
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return std::to_string(A);
            case kParamB: return std::to_string(B);

            default: break;
        }
        return {};
    }

    constexpr std::string_view get_parameter_label(int index) const
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return " ";
            case kParamB: return " ";
        }
        return {};
    }

    void process(T** inputs, T** outputs, long sampleFrames)
    {
        T* in1 = inputs[0];
        T* in2 = inputs[1];
        T* out1 = outputs[0];
        T* out2 = outputs[1];

        double overallscale = 1.0;
        overallscale /= 44100.0;
        overallscale *= getSampleRate();
        speedChase = pow(A, 4);
        depthChase = B;
        double speedSpeed = 300 / (fabs(lastSpeed - speedChase) + 1.0);
        double depthSpeed = 300 / (fabs(lastDepth - depthChase) + 1.0);
        lastSpeed = speedChase;
        lastDepth = depthChase;
        double speed;
        double depth;
        double skew;
        double density;
        double tupi = 3.141592653589793238;
        double control;
        double tempcontrol;
        double thickness;
        double out;
        double bridgerectifier;
        double offset;
        double inputSampleL;
        double inputSampleR;
        double drySampleL;
        double drySampleR;
        while (--sampleFrames >= 0)
        {
            inputSampleL = *in1;
            inputSampleR = *in2;
            if (fabs(inputSampleL) < 1.18e-23) {
                inputSampleL = fpdL * 1.18e-17;
            }
            if (fabs(inputSampleR) < 1.18e-23) {
                inputSampleR = fpdR * 1.18e-17;
            }
            drySampleL = inputSampleL;
            drySampleR = inputSampleR;
            speedAmount = (((speedAmount * speedSpeed) + speedChase) / (speedSpeed + 1.0));
            depthAmount = (((depthAmount * depthSpeed) + depthChase) / (depthSpeed + 1.0));
            speed = 0.0001 + (speedAmount / 1000.0);
            speed /= overallscale;
            depth = 1.0 - pow(1.0 - depthAmount, 5);
            skew = 1.0 + pow(depthAmount, 9);
            density = ((1.0 - depthAmount) * 2.0) - 1.0;
            offset = sin(sweep);
            sweep += speed;
            if (sweep > tupi) {
                sweep -= tupi;
            }
            control = fabs(offset);
            if (density > 0)
            {
                tempcontrol = sin(control);
                control = (control * (1.0 - density)) + (tempcontrol * density);
            }
            else
            {
                tempcontrol = 1 - cos(control);
                control = (control * (1.0 + density)) + (tempcontrol * -density);
            }
            // produce either boosted or starved version of control signal
            // will go from 0 to 1
            thickness = ((control * 2.0) - 1.0) * skew;
            out = fabs(thickness);
            // do L
            bridgerectifier = fabs(inputSampleL);
            if (bridgerectifier > 1.57079633) {
                bridgerectifier = 1.57079633;
            }
            // max value for sine function
            if (thickness > 0) {
                bridgerectifier = sin(bridgerectifier);
            }
            else {
                bridgerectifier = 1 - cos(bridgerectifier);
            }
            // produce either boosted or starved version
            if (inputSampleL > 0) {
                inputSampleL = (inputSampleL * (1 - out)) + (bridgerectifier * out);
            }
            else {
                inputSampleL = (inputSampleL * (1 - out)) - (bridgerectifier * out);
            }
            // blend according to density control
            inputSampleL *= (1.0 - control);
            inputSampleL *= 2.0;
            // apply tremolo, apply gain boost to compensate for volume loss
            inputSampleL = (drySampleL * (1 - depth)) + (inputSampleL * depth);
            // end L
            // do R
            bridgerectifier = fabs(inputSampleR);
            if (bridgerectifier > 1.57079633) {
                bridgerectifier = 1.57079633;
            }
            // max value for sine function
            if (thickness > 0) {
                bridgerectifier = sin(bridgerectifier);
            }
            else {
                bridgerectifier = 1 - cos(bridgerectifier);
            }
            // produce either boosted or starved version
            if (inputSampleR > 0) {
                inputSampleR = (inputSampleR * (1 - out)) + (bridgerectifier * out);
            }
            else {
                inputSampleR = (inputSampleR * (1 - out)) - (bridgerectifier * out);
            }
            // blend according to density control
            inputSampleR *= (1.0 - control);
            inputSampleR *= 2.0;
            // apply tremolo, apply gain boost to compensate for volume loss
            inputSampleR = (drySampleR * (1 - depth)) + (inputSampleR * depth);
            // end R
            // begin 64 bit stereo floating point dither
            // int expon; frexp((double)inputSampleL, &expon);
            fpdL ^= fpdL << 13;
            fpdL ^= fpdL >> 17;
            fpdL ^= fpdL << 5;
            // inputSampleL += ((double(fpdL)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
            // frexp((double)inputSampleR, &expon);
            fpdR ^= fpdR << 13;
            fpdR ^= fpdR >> 17;
            fpdR ^= fpdR << 5;
            // inputSampleR += ((double(fpdR)-uint32_t(0x7fffffff)) * 1.1e-44l * pow(2,expon+62));
            // end 64 bit stereo floating point dither
            *out1 = inputSampleL;
            *out2 = inputSampleR;
            *in1++;
            *in2++;
            *out1++;
            *out2++;
        }
    }
};
} // namespace airwindohhs