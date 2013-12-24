#include "Levels/LevelChangedEventArgs.h"

using namespace Ponykart::Levels;

LevelChangedEventArgs::LevelChangedEventArgs(const Level& NewLevel, const Level& OldLevel, const LevelChangeRequest& Request)
: newLevel(NewLevel), oldLevel(OldLevel), request(Request)
{

}
