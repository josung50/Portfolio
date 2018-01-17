using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CCTV : MonoBehaviour {

    private bool enableCCTV;
    private TPScharacterCtrl.PLAYERSTATE originState;

    // Use this for initialization
    void Start () {
        enableCCTV = false;

    }
	
	// Update is called once per frame
	void Update () {
        UsingCCtV();
    }

    void UsingCCtV()
    {
        if (Input.GetKeyDown(KeyCode.O))
        {
            if (enableCCTV) // 끄기
            {
                TPScharacterCtrl.playerState = originState;
                enableCCTV = false;
                for(int i = 2; i<=5;i++)
                {
                    GameManagerParameter.Instance().cam[i].SetActive(false);
                }
            }
            else // 켜기
            {
                originState = TPScharacterCtrl.playerState;
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.useCCTV;
                enableCCTV = true;
                for (int i = 2; i <= 5; i++)
                {
                    GameManagerParameter.Instance().cam[i].SetActive(true);
                }
            }
        }
    }
}
