#pragma once

class cInputAction
{
public:
	void Init(void);
	void Update(float lfTimestep, float lfValue);
	inline bool GetIsPressed(void) const		{ return mbIsPressed;		}
	inline bool GetIsReleased(void) const		{ return !mbIsPressed;		}
	inline bool GetBecomePressed(void) const	{ return mbBecomePressed;	}
	inline bool GetBecomeReleased(void) const	{ return mbBecomeReleased;	}
	inline float GetPressedTime(void) const		{ return mfTimePressed;		}
	inline float GetValue(void) const			{ return mfValue;			}

private:
	float mfValue;
	float mfTimePressed;
	bool mbIsPressed;
	bool mbWasPressed;
	bool mbBecomeReleased;
	bool mbBecomePressed;

};
