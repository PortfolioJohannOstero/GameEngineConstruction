#ifndef SHEEP_DEBUG_MESSAGE
#define SHEEP_DEBUG_MESSAGE

/*
+=============================================+
+==============================================+
Debug Message.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
The Debug class is semi-purely there to make debugging and testing easier.
it allows the client to output message to a "console" by taking strings and other extensions (that the get turned into strings).
This Class can be accessed from anywhere!

It allows for three different colours, White(normal), Yellow(warning), Red(error)
	By default it will always be white
+==============================================+
+============================================+
*/


#include <HAPI_lib.h>
#include <vector>

namespace Sheep
{
	#define DEBUG_MESSAGE Sheep::DebugMessage::getInstance()

	enum MESSAGE_TYPE
	{
		NORMAL = 0,
		WARNING,
		ERROR
	};

	struct Message
	{
		std::string message;
		MESSAGE_TYPE type;
		DWORD timestamp;

		Message() {}

		Message(const std::string& newMessage, const MESSAGE_TYPE messageType) 
			: message(newMessage), type(messageType) {}
	};

	class Vector2;
	class DebugMessage
	{
	public:
		/* +==== Singleton ====+ */
		static void Create();
		static void Destroy();
		static DebugMessage& getInstance() { return *INSTANCE; }
		bool Initialise(const Vector2& windowPos, unsigned short maxRowOfMessage, unsigned int rowPadding);

		/* +==== Message Handling ====+ */
		void PushMessage(const std::string& message, MESSAGE_TYPE type = MESSAGE_TYPE::NORMAL);
		// Extensions:
		void PushMessage(const Vector2& message, MESSAGE_TYPE type = MESSAGE_TYPE::NORMAL);

		/* +==== Render Text ====+ */
		void RenderMessages();

		/* +=== Toggles ===+ */
		void Display(bool state);
		void DisplayTimeStamp(bool state);
		
		/* +=== Getter ===+ */
		bool isDisplayOn() const;


	private:
		static DebugMessage* INSTANCE;

		HAPI_TColour mErrorColour{ 255, 12, 12 };
		HAPI_TColour mWarningColour{ 255, 255, 12 };
		HAPI_TColour mMessageColour; // <-- white

		std::vector<Message> mMessages;
		unsigned int mIndex = 0;

		Vector2* mWindowPosition = nullptr;
		unsigned int mRowPadding;

		bool mDisplayTimeStamp = true;
		bool mDisplayWindow = true;

		DebugMessage() {}
		~DebugMessage();
	};
}

#endif