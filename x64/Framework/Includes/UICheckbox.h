#ifndef UICHECKBOX_H
#define UICHECKBOX_H

#include <d2d1.h>
#include <string>
#include "Graphics.h"
#include "UIElement.h"

class EventHandler;

class UICheckbox : public UIElement
{
public:
	UICheckbox(UIWindow* srcWindow);
	UICheckbox(UIWindow* srcWindow, std::string text);
	UICheckbox(UIWindow* srcWindow, std::string text, std::string fontName);
	UICheckbox(UIWindow* srcWindow, std::string text, std::string fontName, int FontSize);
	UICheckbox(UIWindow* srcWindow, std::string text, std::string fontName, int FontSize, float xPos, float yPos, float size);

	UICheckbox(UIWindow* srcWindow, std::string text, std::string fontName,
		int FontSize, float xPos, float yPos, float size, float TextWidth, float TextHeight);

	UICheckbox(UIWindow* srcWindow, std::string text, std::string fontName,
		int FontSize, float xPos, float yPos, float size, float TextWidth, float TextHeight, float margins);

	void Draw();

	// Getters
	UIWindow* GetSourceWindow() { return this->srcWindow; }
	std::string GetText() { return this->Text; }
	std::string GetFontName() { return this->FontName; }
	int GetFontSize() { return this->FontSize; }
	float GetPosX() { return this->xPos; }
	float GetPosY() { return this->yPos; }
	float GetSize() { return this->Size; }
	float GetWidth() { return this->Size; }
	float GetHeight() { return this->Size; }
	float GetMargins() { return this->Margins; }
	float GetTextWidth() { return this->TextWidth; }
	float GetTextHeight() { return this->TextHeight; }
	bool GetChecked() { return this->Checked; }
	bool GetVisible() { return this->Visible; }
	bool GetEnabled() { return this->Enabled; }
	bool GetRoundedCorners() { return this->RoundedCorners; }
	float GetRoundCornersRadiusX() { return this->roundCornerRadiusX; }
	float GetRoundCornersRadiusY() { return this->roundCornerRadiusY; }
	Color GetColor() { return this->color; }
	Color GetTextColor() { return this->textColor; }

	// Setters
	void SetText(std::string text) { this->Text = text; }
	void SetFontName(std::string fontName) { this->Text = fontName; }
	void SetTextAllignment(int alligment) { this->TextAllignment = alligment; }
	void SetFontSize(int size) { this->FontSize = size; }
	void SetPosition(float x, float y) { this->xPos = x; this->yPos = y; }
	void SetColor(Color color) { this->color = color; this->normalAlpha = color.a; }
	void SetTextColor(Color color) { this->textColor = color; }
	void SetMargins(float size) { this->Margins = size; }
	void SetSize(float size) { this->Size = size; }
	void SetTextWidth(float w) { this->TextWidth = w; }
	void SetTextHeight(float h) { this->TextHeight = h; }
	void SetChecked(bool state) { this->Checked = state; }
	void SetVisible(bool state) { this->Visible = state; }
	void SetWidth(float size) { this->Size = size; }
	void SetHeight(float size) { this->Size = size; }
	void SetEnabled(bool state)
	{ 
		this->Enabled = state;
		if (state)
		{
			color.a = normalAlpha;
			textColor.a = normalAlpha;
		}
		else
		{
			color.a = 36;
			textColor.a = 36;
		}
	}
	void SetRoundedCorners(bool state) { this->RoundedCorners = state; }
	void SetRoundedCornersRadii(float radX, float radY) { this->roundCornerRadiusX = radX; this->roundCornerRadiusY = radY; }
	void FadeOut(int animationDelay, int decrementValue)
	{
		std::thread t([this, animationDelay, decrementValue] {
			for (int i = color.a; i >= 1; i -= decrementValue)
			{
				Sleep(animationDelay);
				uint8_t val = (uint8_t)i;
				color.a = val;
				this->normalAlpha = color.a;
				this->textColor.a = color.a;
			}
			this->Visible = false;
			return;
		});
		t.detach();
	}
	void FadeIn(int animationDelay, int incrementValue, int finalAlpha)
	{
		if (finalAlpha >= 255)
			finalAlpha = 254;
		std::thread t([this, animationDelay, incrementValue, finalAlpha] {
			this->Visible = true;
			for (int i = color.a; i <= finalAlpha; i += incrementValue)
			{
				Sleep(animationDelay);
				uint8_t val = (uint8_t)i;
				color.a = val;
				this->normalAlpha = color.a;
				this->textColor.a = color.a;
			}
		});
		t.detach();
	}

	// Setters for Event Handlers
	typedef void(*callback_function)(UIElement* sender);
	void SetStateChangedEventHandler(callback_function func);

	virtual ~UICheckbox();

private:
	UIWindow* srcWindow;
	std::string Text = std::string("Checkbox");
	std::string FontName = std::string("Arial");
	int TextAllignment = TEXT_ALLIGNMENT_CENTER;
	int FontSize = 14;
	float xPos = 40, yPos = 30, Size = 20, TextWidth = 100, TextHeight = 20;
	Color color = Color::White;
	Color textColor = Color::Black;
	uint8_t normalAlpha = 255;
	float Margins = 4.0f;
	bool Visible = true;
	bool Enabled = true;
	bool RoundedCorners = true;
	float roundCornerRadiusX = 4, roundCornerRadiusY = 4;

	// Checked State
	bool Checked = false;

	// Entire Label Border
	D2D1_RECT_F LabelBorder;

	// Text Border
	D2D1_RECT_F TextBorder;

	// Event Handlers
	void SetMouseClickHandler(callback_function func);
	EventHandler* MouseClickHandler;
	EventHandler* StateEventHandler;
};


#endif // !UICHECKBOX_H