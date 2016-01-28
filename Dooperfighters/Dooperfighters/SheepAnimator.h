#ifndef SHEEP_ANIMATOR
#define SHEEP_ANIMATOR

namespace Sheep
{
	class Animator
	{
	public:
		Animator(unsigned int startFrame, unsigned int endFrame, bool loopAnimation);
		Animator(const Animator& cpy);

		void Play();
		void Stop();
		void Pause();
		void Increment();
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