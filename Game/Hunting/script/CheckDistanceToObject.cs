using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class CheckDistanceToObject : MonoBehaviour {

    public GameObject point;
    public RaycastHit hit;
    public Text binocularsDistanceText;
    public bool enableAim;

	// Use this for initialization
	void Start () {
        binocularsDistanceText.enabled = false;
	}
	
	// Update is called once per frame
	void Update () {
        if (binocularsDistanceText.enabled)
            CalculationDistance();

    }

    void OnGUI()
    {
        if (TPScharacterCtrl.playerState == TPScharacterCtrl.PLAYERSTATE.useBinoculars)
        {
            binocularsDistanceText.enabled = true;
        }
        else
            binocularsDistanceText.enabled = false;
    }

    void CalculationDistance()
    {
        // 동물 디텍팅 박스 무시
        int layerMask = 1 << 8;
        layerMask = ~layerMask;
        if (Physics.Raycast(point.transform.position, point.transform.forward, out hit, 1000, layerMask))
        {
            Debug.DrawRay(point.transform.position, hit.transform.position, Color.red);
            binocularsDistanceText.text = hit.distance.ToString("N1") + "m";
        }
    }
}
