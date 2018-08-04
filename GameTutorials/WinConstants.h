#pragma once

//const float MAX_WIN = 1.0f;
//const float MIN_WIN = -MAX_WIN;
//const float MAX_POSITIVE = MAX_WIN / 2;
//const float MIN_POSITIVE = -MAX_POSITIVE;
//const float TIE = 0;

const float MAX_WIN = 1.0f;
const float MIN_WIN = -1.0f;
const float MAX_POSITIVE = MAX_WIN / 2;
const float MIN_POSITIVE = -MAX_POSITIVE;
const float TIE = 0;

const float SCORE_SINGLE_TOKEN = MAX_WIN / 5.0f;
const float SCORE_DOUBLE_TOKEN = MAX_WIN / 2.0f;
const float SCORE_TURN_ADVANTAGE = MAX_WIN / 10.0f;