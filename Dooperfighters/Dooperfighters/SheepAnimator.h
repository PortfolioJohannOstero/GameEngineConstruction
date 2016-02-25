#ifndef SHEEP_ANIMATOR
#define SHEEP_ANIMATOR

/*
+=============================================+
+==============================================+
Animator.h
Engine: Sheep Engine
Author: Jóhann Østerø.
--
The Animator class is a support class. It does not change frames by itself, but rather,
allows the client to etablish the number of frames, and where they start and end.
This then allows for pausing/playing and stoping to manipulate the currentframe.
It simply returns an integer that can then be used as a framecount in the VIEW blackbox

This class is a means of making the manipulation of keyframing a bit easier, hence a support class.
+==============================================+
+============================================+
*/

namespace Sheep
{
	class Animator
	{
	public:
		Animator(unsigned int startFrame, unsigned int endFrame, bool loopAnimation);
		Animator(const Animator& cpy);

		void Play(); 
		void Stop(); // <-- Stop resets the "animation"
		void Pause();
		void Increment(); // <-- Needs to be called to move forward in the keyframing
		int getKey();
		void SetCurrentFrame(int frame);
		void SetCurrentFrameToRandomFrame();

	private:
		int mCurrentFrame;
		int mStartFrame;
		int mEndFrame;

		bool mIsPlaying;
		bool mIsLooping;
	};
}

#endif