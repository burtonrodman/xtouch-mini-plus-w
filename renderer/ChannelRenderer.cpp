#include <cstdio>
#include <string>
#include "pico/stdlib.h"

#include "I2C.h"
#include "PioI2C.h"
#include "pio_i2c.h"
// #include "i2c.pio.h"

#include "../oled/OLED.h"
#include "../oled/font/Cherry_Cream_Soda_Regular_16.h"

#include "Renderer.h"
#include "ChannelRenderer.h"
#include "../models/ChannelModel.h"

void ChannelRenderer::drawChannelOled()
{
    _oled->clear();

    // char string1[10];
    // for (int i = 0; i < 4; i++) {
    //     sprintf(string1 + i * 2, "%02X", _model->lastMidiMessage[i]);
    // }
    // std::string message = std::string(string1);
    // _oled->print(0, 0, message);

    auto chanString = formatIntToString("   CHAN %d   ", _model->ChannelNumber);
    _oled->print(0, 0, chanString);

    _oled->drawRectangle(0, 24, 128, 8);
    _oled->drawFilledRectangle(1, 25, _model->EncoderValue / 2, 6);

    if (_model->EncoderPressed) {
        std::string a = std::string("0");
        _oled->print(32, 40, a);
    }

    if (_model->Button1Pressed) {
        std::string b = std::string("1");
        _oled->print(48, 40, b);
    }

    if (_model->Button2Pressed) {
        std::string c = std::string("2");
        _oled->print(64, 40, c);
    }
 
    _oled->show();
}

ChannelRenderer::ChannelRenderer(
    ChannelModel* model,
    OLED* oled
) {
    _model = model;
    _oled = oled;
}

ChannelRenderer::~ChannelRenderer() { }

uint ChannelRenderer::init() {
    return 0;
}

void ChannelRenderer::render() {
    if (_model->Dirty) {
        drawChannelOled();
        _model->Dirty = false;
    }
}