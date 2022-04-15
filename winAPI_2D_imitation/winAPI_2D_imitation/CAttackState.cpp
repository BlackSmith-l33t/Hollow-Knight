#include "framework.h"
#include "CAttackState.h"

CAttackState::CAttackState(MON_STATE state) : CState(state)
{

}

CAttackState::~CAttackState()
{
}

void CAttackState::update()
{
}

void CAttackState::Enter()
{	
}

void CAttackState::Exit()
{
	Logger::debug(L"Attack OUT");
}

void CAttackState::Attack()
{
	Logger::debug(L"Attack ON");
}
