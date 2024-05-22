#pragma once
#include "effect.hpp"
#include <cstdlib>

namespace airwindohhs {
template <typename T>
class Energy2 final : public Effect<T>
{
    const std::string m_name{ "Energy2" };

    uint32_t fpdL;
    uint32_t fpdR;
    // default stuff
    double lastRefL[10];
    double lastRefR[10];
    int cycle;
    double duoEvenL;
    double duoOddL;
    double duoFactorL;
    bool flip;
    double tripletAL;
    double tripletBL;
    double tripletCL;
    double tripletFactorL;
    int countA;
    double quadAL;
    double quadBL;
    double quadCL;
    double quadDL;
    double quadFactorL;
    int countB;
    double quintAL;
    double quintBL;
    double quintCL;
    double quintDL;
    double quintEL;
    double quintFactorL;
    int countC;
    double sextAL;
    double sextBL;
    double sextCL;
    double sextDL;
    double sextEL;
    double sextFL;
    double sextFactorL;
    int countD;
    double septAL;
    double septBL;
    double septCL;
    double septDL;
    double septEL;
    double septFL;
    double septGL;
    double septFactorL;
    int countE;
    double octAL;
    double octBL;
    double octCL;
    double octDL;
    double octEL;
    double octFL;
    double octGL;
    double octHL;
    double octFactorL;
    int countF;
    double nintAL;
    double nintBL;
    double nintCL;
    double nintDL;
    double nintEL;
    double nintFL;
    double nintGL;
    double nintHL;
    double nintIL;
    double nintFactorL;
    int countG;
    double PrevHL;
    double PrevGL;
    double PrevFL;
    double PrevEL;
    double PrevDL;
    double PrevCL;
    double PrevBL;
    double PrevAL;
    double duoEvenR;
    double duoOddR;
    double duoFactorR;
    double tripletAR;
    double tripletBR;
    double tripletCR;
    double tripletFactorR;
    double quadAR;
    double quadBR;
    double quadCR;
    double quadDR;
    double quadFactorR;
    double quintAR;
    double quintBR;
    double quintCR;
    double quintDR;
    double quintER;
    double quintFactorR;
    double sextAR;
    double sextBR;
    double sextCR;
    double sextDR;
    double sextER;
    double sextFR;
    double sextFactorR;
    double septAR;
    double septBR;
    double septCR;
    double septDR;
    double septER;
    double septFR;
    double septGR;
    double septFactorR;
    double octAR;
    double octBR;
    double octCR;
    double octDR;
    double octER;
    double octFR;
    double octGR;
    double octHR;
    double octFactorR;
    double nintAR;
    double nintBR;
    double nintCR;
    double nintDR;
    double nintER;
    double nintFR;
    double nintGR;
    double nintHR;
    double nintIR;
    double nintFactorR;
    double PrevHR;
    double PrevGR;
    double PrevFR;
    double PrevER;
    double PrevDR;
    double PrevCR;
    double PrevBR;
    double PrevAR;
    float A;
    float B;
    float C;
    float D;
    float E;
    float F;
    float G;
    float H;
    float I;

    enum params
    {
        kParamA = 0,
        kParamB = 1,
        kParamC = 2,
        kParamD = 3,
        kParamE = 4,
        kParamF = 5,
        kParamG = 6,
        kParamH = 7,
        kParamI = 8,
        kNumParameters = 9

    };

  public:
    Energy2()
    {
        A = 0.5;
        B = 0.5;
        C = 0.5;
        D = 0.5;
        E = 0.5;
        F = 0.5;
        G = 0.5;
        H = 0.5;
        I = 1.0;
        for (int count = 0; count < 9; count++) {
            lastRefL[count] = 0.0;
            lastRefR[count] = 0.0;
        }
        cycle = 0;
        duoEvenL = 0.0;
        duoOddL = 0.0;
        duoFactorL = 0.0;
        duoEvenR = 0.0;
        duoOddR = 0.0;
        duoFactorR = 0.0;
        flip = false;
        tripletAL = 0.0;
        tripletBL = 0.0;
        tripletCL = 0.0;
        tripletFactorL = 0.0;
        tripletAR = 0.0;
        tripletBR = 0.0;
        tripletCR = 0.0;
        tripletFactorR = 0.0;
        countA = 1;
        quadAL = 0.0;
        quadBL = 0.0;
        quadCL = 0.0;
        quadDL = 0.0;
        quadFactorL = 0.0;
        quadAR = 0.0;
        quadBR = 0.0;
        quadCR = 0.0;
        quadDR = 0.0;
        quadFactorR = 0.0;
        countB = 1;
        quintAL = 0.0;
        quintBL = 0.0;
        quintCL = 0.0;
        quintDL = 0.0;
        quintEL = 0.0;
        quintFactorL = 0.0;
        quintAR = 0.0;
        quintBR = 0.0;
        quintCR = 0.0;
        quintDR = 0.0;
        quintER = 0.0;
        quintFactorR = 0.0;
        countC = 1;
        sextAL = 0.0;
        sextBL = 0.0;
        sextCL = 0.0;
        sextDL = 0.0;
        sextEL = 0.0;
        sextFL = 0.0;
        sextFactorL = 0.0;
        sextAR = 0.0;
        sextBR = 0.0;
        sextCR = 0.0;
        sextDR = 0.0;
        sextER = 0.0;
        sextFR = 0.0;
        sextFactorR = 0.0;
        countD = 1;
        septAL = 0.0;
        septBL = 0.0;
        septCL = 0.0;
        septDL = 0.0;
        septEL = 0.0;
        septFL = 0.0;
        septGL = 0.0;
        septFactorL = 0.0;
        septAR = 0.0;
        septBR = 0.0;
        septCR = 0.0;
        septDR = 0.0;
        septER = 0.0;
        septFR = 0.0;
        septGR = 0.0;
        septFactorR = 0.0;
        countE = 1;
        octAL = 0.0;
        octBL = 0.0;
        octCL = 0.0;
        octDL = 0.0;
        octEL = 0.0;
        octFL = 0.0;
        octGL = 0.0;
        octHL = 0.0;
        octFactorL = 0.0;
        octAR = 0.0;
        octBR = 0.0;
        octCR = 0.0;
        octDR = 0.0;
        octER = 0.0;
        octFR = 0.0;
        octGR = 0.0;
        octHR = 0.0;
        octFactorR = 0.0;
        countF = 1;
        nintAL = 0.0;
        nintBL = 0.0;
        nintCL = 0.0;
        nintDL = 0.0;
        nintEL = 0.0;
        nintFL = 0.0;
        nintGL = 0.0;
        nintHL = 0.0;
        nintIL = 0.0;
        nintFactorL = 0.0;
        nintAR = 0.0;
        nintBR = 0.0;
        nintCR = 0.0;
        nintDR = 0.0;
        nintER = 0.0;
        nintFR = 0.0;
        nintGR = 0.0;
        nintHR = 0.0;
        nintIR = 0.0;
        nintFactorR = 0.0;
        countG = 1;
        PrevHL = 0.0;
        PrevGL = 0.0;
        PrevFL = 0.0;
        PrevEL = 0.0;
        PrevDL = 0.0;
        PrevCL = 0.0;
        PrevBL = 0.0;
        PrevAL = 0.0;
        PrevHR = 0.0;
        PrevGR = 0.0;
        PrevFR = 0.0;
        PrevER = 0.0;
        PrevDR = 0.0;
        PrevCR = 0.0;
        PrevBR = 0.0;
        PrevAR = 0.0;
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

    std::string name() override { return m_name; }

    void set_parameter_value(int index, float value) override
    {
        switch (static_cast<params>(index))
        {
            case kParamA: A = value; break;
            case kParamB: B = value; break;
            case kParamC: C = value; break;
            case kParamD: D = value; break;
            case kParamE: E = value; break;
            case kParamF: F = value; break;
            case kParamG: G = value; break;
            case kParamH: H = value; break;
            case kParamI: I = value; break;

            default: break;
        }
    }

    float get_parameter_value(int index) override
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return A;
            case kParamB: return B;
            case kParamC: return C;
            case kParamD: return D;
            case kParamE: return E;
            case kParamF: return F;
            case kParamG: return G;
            case kParamH: return H;
            case kParamI: return I;

            default: break;
        }
        return 0.0;
    }

    std::string get_parameter_name(int index) override
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return "Hiss";
            case kParamB: return "Glitter";
            case kParamC: return "Rat";
            case kParamD: return "Fizz";
            case kParamE: return "Scrape";
            case kParamF: return "Chug";
            case kParamG: return "Yowr";
            case kParamH: return "Snarl";
            case kParamI: return "I/Dr/Wt";

            default: break;
        }
        return {};
    }

    std::string get_parameter_display(int index) override
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return std::to_string((A * 2.0) - 1.0);
            case kParamB: return std::to_string((B * 2.0) - 1.0);
            case kParamC: return std::to_string((C * 2.0) - 1.0);
            case kParamD: return std::to_string((D * 2.0) - 1.0);
            case kParamE: return std::to_string((E * 2.0) - 1.0);
            case kParamF: return std::to_string((F * 2.0) - 1.0);
            case kParamG: return std::to_string((G * 2.0) - 1.0);
            case kParamH: return std::to_string((H * 2.0) - 1.0);
            case kParamI: return std::to_string((I * 2.0) - 1.0);

            default: break;
        }
        return {};
    }

    std::string get_parameter_label(int index) override
    {
        switch (static_cast<params>(index))
        {
            case kParamA: return "";
            case kParamB: return "";
            case kParamC: return "";
            case kParamD: return "";
            case kParamE: return "";
            case kParamF: return "";
            case kParamG: return "";
            case kParamH: return "";
            case kParamI: return "";
        }
        return {};
    }

    void process(T** inputs, T** outputs, long sampleFrames) override
    {
        T* in1 = inputs[0];
        T* in2 = inputs[1];
        T* out1 = outputs[0];
        T* out2 = outputs[1];

        double overallscale = 1.0;
        overallscale /= 44100.0;
        overallscale *= getSampleRate();
        int cycleEnd = floor(overallscale);
        if (cycleEnd < 1) {
            cycleEnd = 1;
        }
        if (cycleEnd > 4) {
            cycleEnd = 4;
        }
        // this is going to be 2 for 88.1 or 96k, 3 for silly people, 4 for 176 or 192k
        if (cycle > cycleEnd - 1) {
            cycle = cycleEnd - 1; // sanity check
        }
        double duoIntensity = -pow((A * 2.0) - 1.0, 3);
        double tripletIntensity = -pow((B * 2.0) - 1.0, 3);
        double quadIntensity = -pow((C * 2.0) - 1.0, 3);
        double quintIntensity = -pow((D * 2.0) - 1.0, 3);
        double sextIntensity = -pow((E * 2.0) - 1.0, 3);
        double septIntensity = -pow((F * 2.0) - 1.0, 3);
        double octIntensity = -pow((G * 2.0) - 1.0, 3);
        double nintIntensity = -pow((H * 2.0) - 1.0, 3);
        double mix = (I * 2.0) - 1.0;
        // all types of air band are running in parallel, not series
        while (--sampleFrames >= 0)
        {
            double inputSampleL = *in1;
            double inputSampleR = *in2;
            if (fabs(inputSampleL) < 1.18e-23) {
                inputSampleL = fpdL * 1.18e-17;
            }
            if (fabs(inputSampleR) < 1.18e-23) {
                inputSampleR = fpdR * 1.18e-17;
            }
            double drySampleL = inputSampleL;
            double drySampleR = inputSampleR;
            cycle++;
            if (cycle == cycleEnd) { // hit the end point and we do an Energy sample
                double correctionL = 0.0;
                double correctionR = 0.0;
                if (fabs(duoIntensity) > 0.0001) {
                    duoFactorL = PrevAL - inputSampleL;
                    duoFactorR = PrevAR - inputSampleR;
                    if (flip)
                    {
                        duoEvenL += duoFactorL;
                        duoOddL -= duoFactorL;
                        duoFactorL = duoEvenL * duoIntensity;
                        duoEvenR += duoFactorR;
                        duoOddR -= duoFactorR;
                        duoFactorR = duoEvenR * duoIntensity;
                    }
                    else
                    {
                        duoOddL += duoFactorL;
                        duoEvenL -= duoFactorL;
                        duoFactorL = duoOddL * duoIntensity;
                        duoOddR += duoFactorR;
                        duoEvenR -= duoFactorR;
                        duoFactorR = duoOddR * duoIntensity;
                    }
                    duoOddL = (duoOddL - ((duoOddL - duoEvenL) / 256.0)) / 2.0;
                    duoEvenL = (duoEvenL - ((duoEvenL - duoOddL) / 256.0)) / 2.0;
                    correctionL = correctionL + duoFactorL;
                    duoOddR = (duoOddR - ((duoOddR - duoEvenR) / 256.0)) / 2.0;
                    duoEvenR = (duoEvenR - ((duoEvenR - duoOddR) / 256.0)) / 2.0;
                    correctionR = correctionR + duoFactorR;
                    flip = !flip;
                } // finished duo section
                if (fabs(tripletIntensity) > 0.0001) {
                    if (countA < 1 || countA > 3) {
                        countA = 1;
                    }
                    switch (countA)
                    {
                        case 1:
                            tripletFactorL = PrevBL - inputSampleL;
                            tripletAL += tripletFactorL;
                            tripletCL -= tripletFactorL;
                            tripletFactorL = tripletAL * tripletIntensity;
                            tripletFactorR = PrevBR - inputSampleR;
                            tripletAR += tripletFactorR;
                            tripletCR -= tripletFactorR;
                            tripletFactorR = tripletAR * tripletIntensity;
                            break;
                        case 2:
                            tripletFactorL = PrevBL - inputSampleL;
                            tripletBL += tripletFactorL;
                            tripletAL -= tripletFactorL;
                            tripletFactorL = tripletBL * tripletIntensity;
                            tripletFactorR = PrevBR - inputSampleR;
                            tripletBR += tripletFactorR;
                            tripletAR -= tripletFactorR;
                            tripletFactorR = tripletBR * tripletIntensity;
                            break;
                        case 3:
                            tripletFactorL = PrevBL - inputSampleL;
                            tripletCL += tripletFactorL;
                            tripletBL -= tripletFactorL;
                            tripletFactorL = tripletCL * tripletIntensity;
                            tripletFactorR = PrevBR - inputSampleR;
                            tripletCR += tripletFactorR;
                            tripletBR -= tripletFactorR;
                            tripletFactorR = tripletCR * tripletIntensity;
                            break;
                    }
                    tripletAL /= 2.0;
                    tripletBL /= 2.0;
                    tripletCL /= 2.0;
                    correctionL = correctionL + tripletFactorL;
                    tripletAR /= 2.0;
                    tripletBR /= 2.0;
                    tripletCR /= 2.0;
                    correctionR = correctionR + tripletFactorR;
                    countA++;
                } // finished triplet section- 15K
                if (fabs(quadIntensity) > 0.0001) {
                    if (countB < 1 || countB > 4) {
                        countB = 1;
                    }
                    switch (countB)
                    {
                        case 1:
                            quadFactorL = PrevCL - inputSampleL;
                            quadAL += quadFactorL;
                            quadDL -= quadFactorL;
                            quadFactorL = quadAL * quadIntensity;
                            quadFactorR = PrevCR - inputSampleR;
                            quadAR += quadFactorR;
                            quadDR -= quadFactorR;
                            quadFactorR = quadAR * quadIntensity;
                            break;
                        case 2:
                            quadFactorL = PrevCL - inputSampleL;
                            quadBL += quadFactorL;
                            quadAL -= quadFactorL;
                            quadFactorL = quadBL * quadIntensity;
                            quadFactorR = PrevCR - inputSampleR;
                            quadBR += quadFactorR;
                            quadAR -= quadFactorR;
                            quadFactorR = quadBR * quadIntensity;
                            break;
                        case 3:
                            quadFactorL = PrevCL - inputSampleL;
                            quadCL += quadFactorL;
                            quadBL -= quadFactorL;
                            quadFactorL = quadCL * quadIntensity;
                            quadFactorR = PrevCR - inputSampleR;
                            quadCR += quadFactorR;
                            quadBR -= quadFactorR;
                            quadFactorR = quadCR * quadIntensity;
                            break;
                        case 4:
                            quadFactorL = PrevCL - inputSampleL;
                            quadDL += quadFactorL;
                            quadCL -= quadFactorL;
                            quadFactorL = quadDL * quadIntensity;
                            quadFactorR = PrevCR - inputSampleR;
                            quadDR += quadFactorR;
                            quadCR -= quadFactorR;
                            quadFactorR = quadDR * quadIntensity;
                            break;
                    }
                    quadAL /= 2.0;
                    quadBL /= 2.0;
                    quadCL /= 2.0;
                    quadDL /= 2.0;
                    correctionL = correctionL + quadFactorL;
                    quadAR /= 2.0;
                    quadBR /= 2.0;
                    quadCR /= 2.0;
                    quadDR /= 2.0;
                    correctionR = correctionR + quadFactorR;
                    countB++;
                } // finished quad section- 10K
                if (fabs(quintIntensity) > 0.0001) {
                    if (countC < 1 || countC > 5) {
                        countC = 1;
                    }
                    switch (countC)
                    {
                        case 1:
                            quintFactorL = PrevDL - inputSampleL;
                            quintAL += quintFactorL;
                            quintEL -= quintFactorL;
                            quintFactorL = quintAL * quintIntensity;
                            quintFactorR = PrevDR - inputSampleR;
                            quintAR += quintFactorR;
                            quintER -= quintFactorR;
                            quintFactorR = quintAR * quintIntensity;
                            break;
                        case 2:
                            quintFactorL = PrevDL - inputSampleL;
                            quintBL += quintFactorL;
                            quintAL -= quintFactorL;
                            quintFactorL = quintBL * quintIntensity;
                            quintFactorR = PrevDR - inputSampleR;
                            quintBR += quintFactorR;
                            quintAR -= quintFactorR;
                            quintFactorR = quintBR * quintIntensity;
                            break;
                        case 3:
                            quintFactorL = PrevDL - inputSampleL;
                            quintCL += quintFactorL;
                            quintBL -= quintFactorL;
                            quintFactorL = quintCL * quintIntensity;
                            quintFactorR = PrevDR - inputSampleR;
                            quintCR += quintFactorR;
                            quintBR -= quintFactorR;
                            quintFactorR = quintCR * quintIntensity;
                            break;
                        case 4:
                            quintFactorL = PrevDL - inputSampleL;
                            quintDL += quintFactorL;
                            quintCL -= quintFactorL;
                            quintFactorL = quintDL * quintIntensity;
                            quintFactorR = PrevDR - inputSampleR;
                            quintDR += quintFactorR;
                            quintCR -= quintFactorR;
                            quintFactorR = quintDR * quintIntensity;
                            break;
                        case 5:
                            quintFactorL = PrevDL - inputSampleL;
                            quintEL += quintFactorL;
                            quintDL -= quintFactorL;
                            quintFactorL = quintEL * quintIntensity;
                            quintFactorR = PrevDR - inputSampleR;
                            quintER += quintFactorR;
                            quintDR -= quintFactorR;
                            quintFactorR = quintER * quintIntensity;
                            break;
                    }
                    quintAL /= 2.0;
                    quintBL /= 2.0;
                    quintCL /= 2.0;
                    quintDL /= 2.0;
                    quintEL /= 2.0;
                    correctionL = correctionL + quintFactorL;
                    quintAR /= 2.0;
                    quintBR /= 2.0;
                    quintCR /= 2.0;
                    quintDR /= 2.0;
                    quintER /= 2.0;
                    correctionR = correctionR + quintFactorR;
                    countC++;
                } // finished quint section- 8K
                if (fabs(sextIntensity) > 0.0001) {
                    if (countD < 1 || countD > 6) {
                        countD = 1;
                    }
                    switch (countD)
                    {
                        case 1:
                            sextFactorL = PrevEL - inputSampleL;
                            sextAL += sextFactorL;
                            sextFL -= sextFactorL;
                            sextFactorL = sextAL * sextIntensity;
                            sextFactorR = PrevER - inputSampleR;
                            sextAR += sextFactorR;
                            sextFR -= sextFactorR;
                            sextFactorR = sextAR * sextIntensity;
                            break;
                        case 2:
                            sextFactorL = PrevEL - inputSampleL;
                            sextBL += sextFactorL;
                            sextAL -= sextFactorL;
                            sextFactorL = sextBL * sextIntensity;
                            sextFactorR = PrevER - inputSampleR;
                            sextBR += sextFactorR;
                            sextAR -= sextFactorR;
                            sextFactorR = sextBR * sextIntensity;
                            break;
                        case 3:
                            sextFactorL = PrevEL - inputSampleL;
                            sextCL += sextFactorL;
                            sextBL -= sextFactorL;
                            sextFactorL = sextCL * sextIntensity;
                            sextFactorR = PrevER - inputSampleR;
                            sextCR += sextFactorR;
                            sextBR -= sextFactorR;
                            sextFactorR = sextCR * sextIntensity;
                            break;
                        case 4:
                            sextFactorL = PrevEL - inputSampleL;
                            sextDL += sextFactorL;
                            sextCL -= sextFactorL;
                            sextFactorL = sextDL * sextIntensity;
                            sextFactorR = PrevER - inputSampleR;
                            sextDR += sextFactorR;
                            sextCR -= sextFactorR;
                            sextFactorR = sextDR * sextIntensity;
                            break;
                        case 5:
                            sextFactorL = PrevEL - inputSampleL;
                            sextEL += sextFactorL;
                            sextDL -= sextFactorL;
                            sextFactorL = sextEL * sextIntensity;
                            sextFactorR = PrevER - inputSampleR;
                            sextER += sextFactorR;
                            sextDR -= sextFactorR;
                            sextFactorR = sextER * sextIntensity;
                            break;
                        case 6:
                            sextFactorL = PrevEL - inputSampleL;
                            sextFL += sextFactorL;
                            sextEL -= sextFactorL;
                            sextFactorL = sextFL * sextIntensity;
                            sextFactorR = PrevER - inputSampleR;
                            sextFR += sextFactorR;
                            sextER -= sextFactorR;
                            sextFactorR = sextFR * sextIntensity;
                            break;
                    }
                    sextAL /= 2.0;
                    sextBL /= 2.0;
                    sextCL /= 2.0;
                    sextDL /= 2.0;
                    sextEL /= 2.0;
                    sextFL /= 2.0;
                    correctionL = correctionL + sextFactorL;
                    sextAR /= 2.0;
                    sextBR /= 2.0;
                    sextCR /= 2.0;
                    sextDR /= 2.0;
                    sextER /= 2.0;
                    sextFR /= 2.0;
                    correctionR = correctionR + sextFactorR;
                    countD++;
                } // finished sext section- 6K
                if (fabs(septIntensity) > 0.0001) {
                    if (countE < 1 || countE > 7) {
                        countE = 1;
                    }
                    switch (countE)
                    {
                        case 1:
                            septFactorL = PrevFL - inputSampleL;
                            septAL += septFactorL;
                            septGL -= septFactorL;
                            septFactorL = septAL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septAR += septFactorR;
                            septGR -= septFactorR;
                            septFactorR = septAR * septIntensity;
                            break;
                        case 2:
                            septFactorL = PrevFL - inputSampleL;
                            septBL += septFactorL;
                            septAL -= septFactorL;
                            septFactorL = septBL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septBR += septFactorR;
                            septAR -= septFactorR;
                            septFactorR = septBR * septIntensity;
                            break;
                        case 3:
                            septFactorL = PrevFL - inputSampleL;
                            septCL += septFactorL;
                            septBL -= septFactorL;
                            septFactorL = septCL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septCR += septFactorR;
                            septBR -= septFactorR;
                            septFactorR = septCR * septIntensity;
                            break;
                        case 4:
                            septFactorL = PrevFL - inputSampleL;
                            septDL += septFactorL;
                            septCL -= septFactorL;
                            septFactorL = septDL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septDR += septFactorR;
                            septCR -= septFactorR;
                            septFactorR = septDR * septIntensity;
                            break;
                        case 5:
                            septFactorL = PrevFL - inputSampleL;
                            septEL += septFactorL;
                            septDL -= septFactorL;
                            septFactorL = septEL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septER += septFactorR;
                            septDR -= septFactorR;
                            septFactorR = septER * septIntensity;
                            break;
                        case 6:
                            septFactorL = PrevFL - inputSampleL;
                            septFL += septFactorL;
                            septEL -= septFactorL;
                            septFactorL = septFL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septFR += septFactorR;
                            septER -= septFactorR;
                            septFactorR = septFR * septIntensity;
                            break;
                        case 7:
                            septFactorL = PrevFL - inputSampleL;
                            septGL += septFactorL;
                            septFL -= septFactorL;
                            septFactorL = septGL * septIntensity;
                            septFactorR = PrevFR - inputSampleR;
                            septGR += septFactorR;
                            septFR -= septFactorR;
                            septFactorR = septGR * septIntensity;
                            break;
                    }
                    septAL /= 2.0;
                    septBL /= 2.0;
                    septCL /= 2.0;
                    septDL /= 2.0;
                    septEL /= 2.0;
                    septFL /= 2.0;
                    septGL /= 2.0;
                    correctionL = correctionL + septFactorL;
                    septAR /= 2.0;
                    septBR /= 2.0;
                    septCR /= 2.0;
                    septDR /= 2.0;
                    septER /= 2.0;
                    septFR /= 2.0;
                    septGR /= 2.0;
                    correctionR = correctionR + septFactorR;
                    countE++;
                } // finished sept section- 5K
                if (fabs(octIntensity) > 0.0001) {
                    if (countF < 1 || countF > 8) {
                        countF = 1;
                    }
                    switch (countF)
                    {
                        case 1:
                            octFactorL = PrevGL - inputSampleL;
                            octAL += octFactorL;
                            octHL -= octFactorL;
                            octFactorL = octAL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octAR += octFactorR;
                            octHR -= octFactorR;
                            octFactorR = octAR * octIntensity;
                            break;
                        case 2:
                            octFactorL = PrevGL - inputSampleL;
                            octBL += octFactorL;
                            octAL -= octFactorL;
                            octFactorL = octBL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octBR += octFactorR;
                            octAR -= octFactorR;
                            octFactorR = octBR * octIntensity;
                            break;
                        case 3:
                            octFactorL = PrevGL - inputSampleL;
                            octCL += octFactorL;
                            octBL -= octFactorL;
                            octFactorL = octCL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octCR += octFactorR;
                            octBR -= octFactorR;
                            octFactorR = octCR * octIntensity;
                            break;
                        case 4:
                            octFactorL = PrevGL - inputSampleL;
                            octDL += octFactorL;
                            octCL -= octFactorL;
                            octFactorL = octDL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octDR += octFactorR;
                            octCR -= octFactorR;
                            octFactorR = octDR * octIntensity;
                            break;
                        case 5:
                            octFactorL = PrevGL - inputSampleL;
                            octEL += octFactorL;
                            octDL -= octFactorL;
                            octFactorL = octEL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octER += octFactorR;
                            octDR -= octFactorR;
                            octFactorR = octER * octIntensity;
                            break;
                        case 6:
                            octFactorL = PrevGL - inputSampleL;
                            octFL += octFactorL;
                            octEL -= octFactorL;
                            octFactorL = octFL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octFR += octFactorR;
                            octER -= octFactorR;
                            octFactorR = octFR * octIntensity;
                            break;
                        case 7:
                            octFactorL = PrevGL - inputSampleL;
                            octGL += octFactorL;
                            octFL -= octFactorL;
                            octFactorL = octGL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octGR += octFactorR;
                            octFR -= octFactorR;
                            octFactorR = octGR * octIntensity;
                            break;
                        case 8:
                            octFactorL = PrevGL - inputSampleL;
                            octHL += octFactorL;
                            octGL -= octFactorL;
                            octFactorL = octHL * octIntensity;
                            octFactorR = PrevGR - inputSampleR;
                            octHR += octFactorR;
                            octGR -= octFactorR;
                            octFactorR = octHR * octIntensity;
                            break;
                    }
                    octAL /= 2.0;
                    octBL /= 2.0;
                    octCL /= 2.0;
                    octDL /= 2.0;
                    octEL /= 2.0;
                    octFL /= 2.0;
                    octGL /= 2.0;
                    octHL /= 2.0;
                    correctionL = correctionL + octFactorL;
                    octAR /= 2.0;
                    octBR /= 2.0;
                    octCR /= 2.0;
                    octDR /= 2.0;
                    octER /= 2.0;
                    octFR /= 2.0;
                    octGR /= 2.0;
                    octHR /= 2.0;
                    correctionR = correctionR + octFactorR;
                    countF++;
                } // finished oct section- 4K
                if (fabs(nintIntensity) > 0.0001) {
                    if (countG < 1 || countG > 9) {
                        countG = 1;
                    }
                    switch (countG)
                    {
                        case 1:
                            nintFactorL = PrevHL - inputSampleL;
                            nintAL += nintFactorL;
                            nintIL -= nintFactorL;
                            nintFactorL = nintAL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintAR += nintFactorR;
                            nintIR -= nintFactorR;
                            nintFactorR = nintAR * nintIntensity;
                            break;
                        case 2:
                            nintFactorL = PrevHL - inputSampleL;
                            nintBL += nintFactorL;
                            nintAL -= nintFactorL;
                            nintFactorL = nintBL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintBR += nintFactorR;
                            nintAR -= nintFactorR;
                            nintFactorR = nintBR * nintIntensity;
                            break;
                        case 3:
                            nintFactorL = PrevHL - inputSampleL;
                            nintCL += nintFactorL;
                            nintBL -= nintFactorL;
                            nintFactorL = nintCL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintCR += nintFactorR;
                            nintBR -= nintFactorR;
                            nintFactorR = nintCR * nintIntensity;
                            break;
                        case 4:
                            nintFactorL = PrevHL - inputSampleL;
                            nintDL += nintFactorL;
                            nintCL -= nintFactorL;
                            nintFactorL = nintDL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintDR += nintFactorR;
                            nintCR -= nintFactorR;
                            nintFactorR = nintDR * nintIntensity;
                            break;
                        case 5:
                            nintFactorL = PrevHL - inputSampleL;
                            nintEL += nintFactorL;
                            nintDL -= nintFactorL;
                            nintFactorL = nintEL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintER += nintFactorR;
                            nintDR -= nintFactorR;
                            nintFactorR = nintER * nintIntensity;
                            break;
                        case 6:
                            nintFactorL = PrevHL - inputSampleL;
                            nintFL += nintFactorL;
                            nintEL -= nintFactorL;
                            nintFactorL = nintFL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintFR += nintFactorR;
                            nintER -= nintFactorR;
                            nintFactorR = nintFR * nintIntensity;
                            break;
                        case 7:
                            nintFactorL = PrevHL - inputSampleL;
                            nintGL += nintFactorL;
                            nintFL -= nintFactorL;
                            nintFactorL = nintGL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintGR += nintFactorR;
                            nintFR -= nintFactorR;
                            nintFactorR = nintGR * nintIntensity;
                            break;
                        case 8:
                            nintFactorL = PrevHL - inputSampleL;
                            nintHL += nintFactorL;
                            nintGL -= nintFactorL;
                            nintFactorL = nintHL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintHR += nintFactorR;
                            nintGR -= nintFactorR;
                            nintFactorR = nintHR * nintIntensity;
                            break;
                        case 9:
                            nintFactorL = PrevHL - inputSampleL;
                            nintIL += nintFactorL;
                            nintHL -= nintFactorL;
                            nintFactorL = nintIL * nintIntensity;
                            nintFactorR = PrevHR - inputSampleR;
                            nintIR += nintFactorR;
                            nintHR -= nintFactorR;
                            nintFactorR = nintIR * nintIntensity;
                            break;
                    }
                    nintAL /= 2.0;
                    nintBL /= 2.0;
                    nintCL /= 2.0;
                    nintDL /= 2.0;
                    nintEL /= 2.0;
                    nintFL /= 2.0;
                    nintGL /= 2.0;
                    nintHL /= 2.0;
                    nintIL /= 2.0;
                    correctionL = correctionL + nintFactorL;
                    nintAR /= 2.0;
                    nintBR /= 2.0;
                    nintCR /= 2.0;
                    nintDR /= 2.0;
                    nintER /= 2.0;
                    nintFR /= 2.0;
                    nintGR /= 2.0;
                    nintHR /= 2.0;
                    nintIR /= 2.0;
                    correctionR = correctionR + nintFactorR;
                    countG++;
                } // finished nint section- 3K
                PrevHL = PrevGL;
                PrevGL = PrevFL;
                PrevFL = PrevEL;
                PrevEL = PrevDL;
                PrevDL = PrevCL;
                PrevCL = PrevBL;
                PrevBL = PrevAL;
                PrevAL = inputSampleL;
                PrevHR = PrevGR;
                PrevGR = PrevFR;
                PrevFR = PrevER;
                PrevER = PrevDR;
                PrevDR = PrevCR;
                PrevCR = PrevBR;
                PrevBR = PrevAR;
                PrevAR = inputSampleR;
                inputSampleL = correctionL * mix;
                inputSampleR = correctionR * mix;
                if (cycleEnd == 4) {
                    lastRefL[0] = lastRefL[4]; // start from previous last
                    lastRefL[2] = (lastRefL[0] + inputSampleL) / 2; // half
                    lastRefL[1] = (lastRefL[0] + lastRefL[2]) / 2; // one quarter
                    lastRefL[3] = (lastRefL[2] + inputSampleL) / 2; // three quarters
                    lastRefL[4] = inputSampleL; // full
                    lastRefR[0] = lastRefR[4]; // start from previous last
                    lastRefR[2] = (lastRefR[0] + inputSampleR) / 2; // half
                    lastRefR[1] = (lastRefR[0] + lastRefR[2]) / 2; // one quarter
                    lastRefR[3] = (lastRefR[2] + inputSampleR) / 2; // three quarters
                    lastRefR[4] = inputSampleR; // full
                }
                if (cycleEnd == 3) {
                    lastRefL[0] = lastRefL[3]; // start from previous last
                    lastRefL[2] = (lastRefL[0] + lastRefL[0] + inputSampleL) / 3; // third
                    lastRefL[1] = (lastRefL[0] + inputSampleL + inputSampleL) / 3; // two thirds
                    lastRefL[3] = inputSampleL; // full
                    lastRefR[0] = lastRefR[3]; // start from previous last
                    lastRefR[2] = (lastRefR[0] + lastRefR[0] + inputSampleR) / 3; // third
                    lastRefR[1] = (lastRefR[0] + inputSampleR + inputSampleR) / 3; // two thirds
                    lastRefR[3] = inputSampleR; // full
                }
                if (cycleEnd == 2) {
                    lastRefL[0] = lastRefL[2]; // start from previous last
                    lastRefL[1] = (lastRefL[0] + inputSampleL) / 2; // half
                    lastRefL[2] = inputSampleL; // full
                    lastRefR[0] = lastRefR[2]; // start from previous last
                    lastRefR[1] = (lastRefR[0] + inputSampleR) / 2; // half
                    lastRefR[2] = inputSampleR; // full
                }
                if (cycleEnd == 1) {
                    lastRefL[0] = inputSampleL;
                    lastRefR[0] = inputSampleR;
                }
                cycle = 0; // reset
                inputSampleL = lastRefL[cycle];
                inputSampleR = lastRefR[cycle];
            }
            else {
                inputSampleL = lastRefL[cycle];
                inputSampleR = lastRefR[cycle];
                // we are going through our references now
            }
            switch (cycleEnd) // multi-pole average using lastRef[] variables
            {
                case 4:
                    lastRefL[8] = inputSampleL;
                    inputSampleL = (inputSampleL + lastRefL[7]) * 0.5;
                    lastRefL[7] = lastRefL[8]; // continue, do not break
                    lastRefR[8] = inputSampleR;
                    inputSampleR = (inputSampleR + lastRefR[7]) * 0.5;
                    lastRefR[7] = lastRefR[8]; // continue, do not break
                case 3:
                    lastRefL[8] = inputSampleL;
                    inputSampleL = (inputSampleL + lastRefL[6]) * 0.5;
                    lastRefL[6] = lastRefL[8]; // continue, do not break
                    lastRefR[8] = inputSampleR;
                    inputSampleR = (inputSampleR + lastRefR[6]) * 0.5;
                    lastRefR[6] = lastRefR[8]; // continue, do not break
                case 2:
                    lastRefL[8] = inputSampleL;
                    inputSampleL = (inputSampleL + lastRefL[5]) * 0.5;
                    lastRefL[5] = lastRefL[8]; // continue, do not break
                    lastRefR[8] = inputSampleR;
                    inputSampleR = (inputSampleR + lastRefR[5]) * 0.5;
                    lastRefR[5] = lastRefR[8]; // continue, do not break
                case 1:
                    break; // no further averaging
            }
            inputSampleL += drySampleL;
            inputSampleR += drySampleR;
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
            in1++;
            in2++;
            out1++;
            out2++;
        }
    }
};
} // namespace airwindohhs
