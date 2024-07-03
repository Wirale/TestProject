#include "UI/ResourceWidget.h"
#include "Components/TextBlock.h"

void UResourceWidget::UpdateResource(int NewResource)
{
	ResourceTextBlock->SetText(FText::AsNumber(NewResource));
}
