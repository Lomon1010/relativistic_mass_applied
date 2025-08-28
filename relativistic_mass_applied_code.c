void PM_Accelerate (vec3_t wishdir, float wishspeed, float accel)
{
	int			i;
	float		addspeed, accelspeed, currentspeed;
	float		currentTotalSpeed, relativisticMass;
	
	if (pmove.dead)
		return;
	if (pmove.waterjumptime)
		return;
		
	currentspeed = DotProduct (pmove.velocity, wishdir);
	addspeed = wishspeed - currentspeed;
	if (addspeed <= 0)
		return;
	
	// === 상대론적 질량 효과 ===
	currentTotalSpeed = VectorLength(pmove.velocity);
	float c = 600.0f; // 게임 내 속도의 한계라고 가정. (게임 상황에 맞게 조절 필요)
	float restMass = 1.0f; // 정지 질량
	
	// 안전장치: 최대 속력에 너무 가까우면 제한
	if (currentTotalSpeed >= c * 0.99f) {
		currentTotalSpeed = c * 0.99f;
	}
	
	// 상대론적 질량 계산
	float velocityRatio = currentTotalSpeed / c;
	float velocityRatioSquared = velocityRatio * velocityRatio;
	float relativeMass = restMass / sqrt(1.0f - velocityRatioSquared);
	
	// 속도 변화량 계산
	accelspeed = accel * frametime * wishspeed; // 속도 변화량
	
	// 상대론적 질량 효과로 속도 변화량이 감소
	accelspeed /= relativeMass;
	
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	for (i=0 ; i<3 ; i++)
		pmove.velocity[i] += accelspeed*wishdir[i];
}
