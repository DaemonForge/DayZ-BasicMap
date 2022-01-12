class BM_Navigator extends ItemBase
{	
	
	override void OnWorkStart()
	{
		
		super.OnWorkStart();
	}
	
	override void OnWork( float consumed_energy )
	{
		super.OnWork( consumed_energy );
	}
	
	override void OnWorkStop()
	{
		super.OnWorkStop();
		
	}
	
	
	// Inventory manipulation
	override void OnInventoryExit(Man player)
	{
		super.OnInventoryExit(player);
		
	}
	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionTurnOnWhileInHands);
		AddAction(ActionTurnOffWhileInHands);
	}
}