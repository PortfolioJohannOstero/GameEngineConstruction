#include "SheepAnimator.h"
#include <random>


using namespace Sheep;

Animator::Animator(unsigned int startFrame, unsigned int endFrame, bool loopAnimation)
	: mStartFrame(startFrame), mCurrentFrame(startFrame), mIsPlaying(false), mIsLooping(loopAnimation)
{
	mEndFrame = (endFrame < startFrame) ? startFrame : endFrame;
}

Animator::Animator(const Animator& cpy)
{
	mStartFrame = cpy.mStartFrame;
	mEndFrame = cpy.mEndFrame;
	mCurrentFrame = cpy.mCurrentFrame;
}

void Animator::Play()
{
	mIsPlaying = true;
}

void Animator::Stop()
{
	mIsPlaying = false;
	mCurrentFrame = mStartFrame;
}

void Animator::Pause()
{
	mIsPlaying = false;
}

void Animator::Increment()
{
	if (mIsPlaying)
	{
		if (mCurrentFrame++ > mEndFrame)
		{
			if (mIsLooping)
				mCurrentFrame = mStartFrame;
			else
				Stop();
		}
	}
}

void Animator::SetCurrentFrame(int frame)
{
	if (frame < mStartFrame)
		frame = mStartFrame;
	else if (frame > mEndFrame)
		frame = mEndFrame;
	
	mCurrentFrame = frame;
}

void Animator::SetCurrentFrameToRandomFrame()
{
	mCurrentFrame = mStartFrame + std::rand() % ((mEndFrame + 1) - mStartFrame);
}

int Animator::getKey()
{
	return mCurrentFrame;
}