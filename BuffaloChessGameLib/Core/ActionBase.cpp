#include "Common.h"
#include "ActionBase.h"


ActionBase::ActionBase() :
	m_hint()
{}

ActionBase::~ActionBase()
{}

const Action *const ActionBase::GetHint()
{
	return &m_hint;
}
