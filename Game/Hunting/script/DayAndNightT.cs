using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DayAndNightT : MonoBehaviour {

    // 12시부터 시작, 현실 1초 = 게임시간 1분으로 설정
    // 360/(size*60)==x --> 현실 x 시간 = 게임 24시간
    // ex) size = 0.3 이면 현실 20분 = 게임 24시간

    /* 0도 : 정오, 90도 : 서쪽 지평선, 180 : 반대편, 270 : 동쪽 지평선(해뜸)
     */


    public float size;
    private float ambientIntensityGap;
    public GameObject fire;

    // Use this for initialization
    void Start () {
        ambientIntensityGap = 0.00888f; // 0.8 / 90 (ambientIntensity가 1 ~ 0.2의 범위)

    }
	
	// Update is called once per frame
	void Update () {
        RotateSun();
        ChangeLightColor();
        FireOn();
    }

    void ChangeLightColor()
    {
        // Intensity multiple 조절 1 : 정오(0도) , 0.2 : 00시(180도)
        if (gameObject.transform.eulerAngles.z >= 0 && gameObject.transform.eulerAngles.z <= 90) // 해가 저뭄
        {
            float temp = 1 - ambientIntensityGap * gameObject.transform.eulerAngles.z;
            float temp2 = 1 - (Mathf.Pow(gameObject.transform.eulerAngles.z, 2) * 0.0001f);
            RenderSettings.ambientIntensity = temp;
            RenderSettings.reflectionIntensity = temp;
            RenderSettings.sun.color = new Color(temp2, temp, temp, 0);
            //Debug.Log(RenderSettings.sun.color);
        }
        else if (gameObject.transform.eulerAngles.z >= 270 && gameObject.transform.eulerAngles.z <= 360)
        {
            float temp = 0.2f + ambientIntensityGap * (gameObject.transform.eulerAngles.z - 270);
            float temp2 = 0.2f + (Mathf.Pow(gameObject.transform.eulerAngles.z - 270, 2) * 0.0001f);
            RenderSettings.ambientIntensity = temp;
            RenderSettings.reflectionIntensity = temp;
            RenderSettings.sun.color = new Color(temp2, temp, temp, 0);
        }
    }

    void RotateSun()
    {
        gameObject.transform.eulerAngles += new Vector3(0, 0, size * Time.deltaTime);
    }

    void FireOn()
    {
        if (gameObject.transform.eulerAngles.z >= 75 && gameObject.transform.eulerAngles.z <= 265)
            fire.SetActive(true);
        else
            fire.SetActive(false);
    }
}
