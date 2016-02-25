#include "SheepDebugMessage.h"
#include "Vector2.h"
#include "Rect.h"

using namespace Sheep;

DebugMessage* DebugMessage::INSTANCE = nullptr;
#pragma region Singleton
void DebugMessage::Create()
{
	/* If instance has not been created */
	if (!INSTANCE)
		INSTANCE = new DebugMessage();
}

void DebugMessage::Destroy()
{
	/* If instance has been created */
	if (INSTANCE)
	{
		delete INSTANCE;
		INSTANCE = nullptr;
	}
}

bool DebugMessage::Initialise(const Vector2& windowPos, unsigned short maxRowOfMessage, unsigned int rowPadding)
{
	/* Check if the instance has been created and if the happy initialize */
	if (!INSTANCE)
		return false;

	mWindowPosition = new Vector2(windowPos);
	mRowPadding = rowPadding;
	mMessages.resize(maxRowOfMessage);

	return true;
}

DebugMessage::~DebugMessage()
{
	delete mWindowPosition;
	mMessages.clear();
}
#pragma endregion


void DebugMessage::PushMessage(const std::string& message, MESSAGE_TYPE type)
{
	if (mIndex > mMessages.size()-1)
		mIndex = 0;

	mMessages[mIndex] = Message(message, type);
	mMessages[mIndex].timestamp = HAPI->GetTime();
	mIndex++;
}

void DebugMessage::PushMessage(const Vector2& message, MESSAGE_TYPE type)
{
	PushMessage("x: " + std::to_string(message.x) + " - y: " + std::to_string(message.y), type);
}

/* +=== Toggles ===+ */
void DebugMessage::Display(bool state)
{
	mDisplayWindow = state;
}

void DebugMessage::DisplayTimeStamp(bool state)
{
	mDisplayTimeStamp = state;
}

/* +=== Getter ===+ */
bool DebugMessage::isDisplayOn() const
{
	return mDisplayWindow;
}


void DebugMessage::RenderMessages()
{
	if (mDisplayWindow)
	{
		const HAPI_TColour* colour;
		int yOffset = 0;
		for (auto& message : mMessages)
		{
			if (message.message.empty())
				continue;

			switch (message.type)
			{
			case MESSAGE_TYPE::NORMAL:
				colour = &mMessageColour;
				break;
			case MESSAGE_TYPE::WARNING:
				colour = &mWarningColour;
				break;
			case MESSAGE_TYPE::ERROR:
				colour = &mErrorColour;
			}

			if (mDisplayTimeStamp)
				HAPI->RenderText((int)mWindowPosition->x, (int)mWindowPosition->y + (yOffset * mRowPadding), *colour, std::to_string(message.timestamp / 1000) + "s: " + message.message);
			else
				HAPI->RenderText((int)mWindowPosition->x, (int)mWindowPosition->y + (yOffset * mRowPadding), *colour, message.message);

			yOffset++;
		}
	}
}