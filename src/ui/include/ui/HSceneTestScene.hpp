//
// Purpur Tentakel
// 01.10.2022
//

#pragma once
#include "ui_lib/Scene.h"
#include "helper/HUIAlias.hpp"

/**
 * no doc here.
 * this contains the test scene that is only unused to display new features temporary.
 */
class TestScene : public Scene {
private:
	void Initialize(AppContext_ty appContext);

public:
	TestScene();
	void SetActive(bool active, AppContext_ty_c appContext) override;

	void TestLambda(bool toggled);


	void CheckAndUpdate(Vector2 const& mousePosition, AppContext_ty_c appContext) override;
	void Render(AppContext_ty_c appContext) override;
	void Resize(AppContext_ty_c appContext) override;
};
