#pragma once
#include "effect.hpp"
#include <cstdlib>

namespace airwindohhs {
template <typename T>
class ButterComp2 final : public Effect<T>
{
    std::string m_name{ "ButterComp2" };

    double controlAposL;
    double controlAnegL;
    double controlBposL;
    double controlBnegL;
    double targetposL;
    double targetnegL;
    double lastOutputL;
    double controlAposR;
    double controlAnegR;
    double controlBposR;
    double controlBnegR;
    double targetposR;
    double targetnegR;
    double lastOutputR;
    bool flip;
    uint32_t fpdL;
    uint32_t fpdR;
    // default stuff
    float A;
    float B;
    float C;

    enum params
    {
        kParamcontrolAposL = 0,
        kParamcontrolAnegL = 1,
        kParamcontrolBposL = 2,
        kNumParameters = 3

    };

  public:
    ButterComp2()
    {
        controlAposL = 1.0;
        controlAnegL = 1.0;
        controlBposL = 1.0;
        controlBnegL = 1.0;
        targetposL = 1.0;
        targetnegL = 1.0;
        lastOutputL = 0.0;
        controlAposR = 1.0;
        controlAnegR = 1.0;
        controlBposR = 1.0;
        controlBnegR = 1.0;
        targetposR = 1.0;
        targetnegR = 1.0;
        lastOutputR = 0.0;
        flip = false;
        A = 0.0;
        B = 0.5;
        C = 1.0;
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
            case kParamcontrolAposL: controlAposL = value; break;
            case kParamcontrolAnegL: controlAnegL = value; break;
            case kParamcontrolBposL: controlBposL = value; break;

            default: break;
        }
    }

    float get_parameter_value(int index)
    {
        switch (static_cast<params>(index))
        {
            case kParamcontrolAposL: return controlAposL;
            case kParamcontrolAnegL: return controlAnegL;
            case kParamcontrolBposL: return controlBposL;

            default: break;
        }
        return 0.0;
    }

    constexpr std::string_view get_parameter_name(int index)
    {
        switch (static_cast<params>(index))
        {
            case kParamcontrolAposL: return "Compress";
            case kParamcontrolAnegL: return "Output";
            case kParamcontrolBposL: return "Dry/Wet";

            default: break;
        }
        return {};
    }

    std::string get_parameter_display(int index) const
    {
        switch (static_cast<params>(index))
        {
            case kParamcontrolAposL: return std::to_string(A);
            case kParamcontrolAnegL: return std::to_string(B * 2.0);
            case kParamcontrolBposL: return std::to_string(C);

            default: break;
        }
        return {};
    }

    constexpr std::string_view get_parameter_label(int index) const
    {
        switch (static_cast<params>(index))
        {
            case kParamcontrolAposL: return "";
            case kParamcontrolAnegL: return "";
            case kParamcontrolBposL: return "";
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
        double inputgain = pow(10.0, (A * 14.0) / 20.0);
        double compfactor = 0.012 * (A / 135.0);
        double output = B * 2.0;
        double wet = C;
        // removed extra dry variable
        double outputgain = inputgain;
        outputgain -= 1.0;
        outputgain /= 1.5;
        outputgain += 1.0;
        while (--sampleFrames >= 0)
        {
            double inputSampleL = *in1;
            double inputSampleR = *in2;
            static int noisesourceL = 0;
            static int noisesourceR = 850010;
            int residue;
            double applyresidue;
            noisesourceL = noisesourceL % 1700021;
            noisesourceL++;
            residue = noisesourceL * noisesourceL;
            residue = residue % 170003;
            residue *= residue;
            residue = residue % 17011;
            residue *= residue;
            residue = residue % 1709;
            residue *= residue;
            residue = residue % 173;
            residue *= residue;
            residue = residue % 17;
            applyresidue = residue;
            applyresidue *= 0.00000001;
            applyresidue *= 0.00000001;
            inputSampleL += applyresidue;
            if (inputSampleL < 1.2e-38 && -inputSampleL < 1.2e-38) {
                inputSampleL -= applyresidue;
            }
            noisesourceR = noisesourceR % 1700021;
            noisesourceR++;
            residue = noisesourceR * noisesourceR;
            residue = residue % 170003;
            residue *= residue;
            residue = residue % 17011;
            residue *= residue;
            residue = residue % 1709;
            residue *= residue;
            residue = residue % 173;
            residue *= residue;
            residue = residue % 17;
            applyresidue = residue;
            applyresidue *= 0.00000001;
            applyresidue *= 0.00000001;
            inputSampleR += applyresidue;
            if (inputSampleR < 1.2e-38 && -inputSampleR < 1.2e-38) {
                inputSampleR -= applyresidue;
            }
            // for live air, we always apply the dither noise. Then, if our result is
            // effectively digital black, we'll subtract it aButterComp2. We want a 'air' hiss
            double drySampleL = inputSampleL;
            double drySampleR = inputSampleR;
            inputSampleL *= inputgain;
            inputSampleR *= inputgain;
            double divisor = compfactor / (1.0 + fabs(lastOutputL));
            // this is slowing compressor recovery while output waveforms were high
            divisor /= overallscale;
            double remainder = divisor;
            divisor = 1.0 - divisor;
            // recalculate divisor every sample
            double inputposL = inputSampleL + 1.0;
            if (inputposL < 0.0) {
                inputposL = 0.0;
            }
            double outputposL = inputposL / 2.0;
            if (outputposL > 1.0) {
                outputposL = 1.0;
            }
            inputposL *= inputposL;
            targetposL *= divisor;
            targetposL += (inputposL * remainder);
            double calcposL = pow((1.0 / targetposL), 2);
            double inputnegL = (-inputSampleL) + 1.0;
            if (inputnegL < 0.0) {
                inputnegL = 0.0;
            }
            double outputnegL = inputnegL / 2.0;
            if (outputnegL > 1.0) {
                outputnegL = 1.0;
            }
            inputnegL *= inputnegL;
            targetnegL *= divisor;
            targetnegL += (inputnegL * remainder);
            double calcnegL = pow((1.0 / targetnegL), 2);
            // now we have mirrored targets for comp
            // outputpos and outputneg go from 0 to 1
            if (inputSampleL > 0)
            { // working on pos
                if (flip)
                {
                    controlAposL *= divisor;
                    controlAposL += (calcposL * remainder);
                }
                else
                {
                    controlBposL *= divisor;
                    controlBposL += (calcposL * remainder);
                }
            }
            else
            { // working on neg
                if (flip)
                {
                    controlAnegL *= divisor;
                    controlAnegL += (calcnegL * remainder);
                }
                else
                {
                    controlBnegL *= divisor;
                    controlBnegL += (calcnegL * remainder);
                }
            }
            // this causes each of the four to update only when active and in the correct 'flip'
            divisor = compfactor / (1.0 + fabs(lastOutputR));
            // this is slowing compressor recovery while output waveforms were high
            divisor /= overallscale;
            remainder = divisor;
            divisor = 1.0 - divisor;
            // recalculate divisor every sample
            double inputposR = inputSampleR + 1.0;
            if (inputposR < 0.0) {
                inputposR = 0.0;
            }
            double outputposR = inputposR / 2.0;
            if (outputposR > 1.0) {
                outputposR = 1.0;
            }
            inputposR *= inputposR;
            targetposR *= divisor;
            targetposR += (inputposR * remainder);
            double calcposR = pow((1.0 / targetposR), 2);
            double inputnegR = (-inputSampleR) + 1.0;
            if (inputnegR < 0.0) {
                inputnegR = 0.0;
            }
            double outputnegR = inputnegR / 2.0;
            if (outputnegR > 1.0) {
                outputnegR = 1.0;
            }
            inputnegR *= inputnegR;
            targetnegR *= divisor;
            targetnegR += (inputnegR * remainder);
            double calcnegR = pow((1.0 / targetnegR), 2);
            // now we have mirrored targets for comp
            // outputpos and outputneg go from 0 to 1
            if (inputSampleR > 0)
            { // working on pos
                if (flip)
                {
                    controlAposR *= divisor;
                    controlAposR += (calcposR * remainder);
                }
                else
                {
                    controlBposR *= divisor;
                    controlBposR += (calcposR * remainder);
                }
            }
            else
            { // working on neg
                if (flip)
                {
                    controlAnegR *= divisor;
                    controlAnegR += (calcnegR * remainder);
                }
                else
                {
                    controlBnegR *= divisor;
                    controlBnegR += (calcnegR * remainder);
                }
            }
            // this causes each of the four to update only when active and in the correct 'flip'
            double totalmultiplierL;
            double totalmultiplierR;
            if (flip)
            {
                totalmultiplierL = (controlAposL * outputposL) + (controlAnegL * outputnegL);
                totalmultiplierR = (controlAposR * outputposR) + (controlAnegR * outputnegR);
            }
            else
            {
                totalmultiplierL = (controlBposL * outputposL) + (controlBnegL * outputnegL);
                totalmultiplierR = (controlBposR * outputposR) + (controlBnegR * outputnegR);
            }
            // this combines the sides according to flip, blending relative to the input value
            inputSampleL *= totalmultiplierL;
            inputSampleL /= outputgain;
            inputSampleR *= totalmultiplierR;
            inputSampleR /= outputgain;
            if (output != 1.0) {
                inputSampleL *= output;
                inputSampleR *= output;
            }
            if (wet != 1.0) {
                inputSampleL = (inputSampleL * wet) + (drySampleL * (1.0 - wet));
                inputSampleR = (inputSampleR * wet) + (drySampleR * (1.0 - wet));
            }
            lastOutputL = inputSampleL;
            lastOutputR = inputSampleR;
            // we will make this factor respond to use of dry/wet
            flip = !flip;
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