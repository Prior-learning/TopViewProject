#include "CHUD.h"
#include "CEnemyHpWidget.h"


void ACHUD::AddViewEnemyHpbar()
{
    BossBar = CreateWidget<UUserWidget>(GetOwningPlayerController(), classof, FName("BossBar"));
    UCEnemyHpWidget::instance = Cast<UCEnemyHpWidget>( BossBar);

}