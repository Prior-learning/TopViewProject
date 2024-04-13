#include "TargetDownWidget.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UTargetDownWidget::UTargetDownWidget(const FObjectInitializer &ObjectInitializer) 
    : Super(ObjectInitializer)
{

}

void UTargetDownWidget::FollowMousePos()
{
    if (ScopeImage)
    {
        FVector2D MousePosition;
        UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePosition.X, MousePosition.Y);
        // ������ �̹����� ��ġ�� ���콺 ��ġ�� ����
        ScopeImage->SetRenderTranslation(MousePosition);
    }
}

void UTargetDownWidget::NativeConstruct()
{
    Super::NativeConstruct();
    AddToViewport();
  
}

void UTargetDownWidget::NativeTick(const FGeometry &MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    if(GetVisibility()==ESlateVisibility::Visible)
    {
        FollowMousePos();
    }
   
}
