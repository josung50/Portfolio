using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Map : MonoBehaviour {

    private TPScharacterCtrl.PLAYERSTATE originState;

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		if(Input.GetKeyDown(KeyCode.M) ) { 
            if(TPScharacterCtrl.playerState != TPScharacterCtrl.PLAYERSTATE.useMap) // 켜기
            {
                originState = TPScharacterCtrl.playerState;
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.useMap;
                GameManagerParameter.Instance().cam[6].SetActive(true);
            }
            else // 끄기
            {
                TPScharacterCtrl.playerState = originState;
                GameManagerParameter.Instance().cam[6].SetActive(false);
            }
        }
	}
}
