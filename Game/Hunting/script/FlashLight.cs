using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FlashLight : MonoBehaviour {

    public float batteryLife;
    public Sprite[] batterImg;
    public Image batteryImgCast;

    public GameObject flashLight;
    public static float batteryTimer;
    private bool onOff;
    private float timeSlot; // batteryLife를 5등분

    // Use this for initialization
    void Start () {
        onOff = false;
        batteryTimer = 0;
        timeSlot = batteryLife / 4;
    }
	
	// Update is called once per frame
	void Update () {
        if(batteryTimer == 0)
            batteryImgCast.sprite = batterImg[4];

        if (Input.GetKeyDown(KeyCode.L))
        {
            if(onOff) // 끄기
            {
                flashLight.SetActive(false);
                onOff = false;
            }
            else if(onOff == false && batteryTimer < batteryLife) // 켜기
            {
                batteryImgCast = GameManagerParameter.Instance().canvas[1].transform.Find("battery").GetComponent<Image>();
                flashLight.SetActive(true);
                onOff = true;
            }
        }

        if (onOff)
            SpendBatteryLife();
	}

    void SpendBatteryLife()
    {
        batteryTimer += Time.deltaTime;
        if (batteryTimer < timeSlot && batteryTimer >= 0) // 건전지 만땅
        {
            batteryImgCast.sprite = batterImg[4];
        }
        else if (batteryTimer < timeSlot * 2 && batteryTimer >= timeSlot * 1)
        {
            batteryImgCast.sprite = batterImg[3];
        }
        else if (batteryTimer < timeSlot * 3 && batteryTimer >= timeSlot * 2)
        {
            batteryImgCast.sprite = batterImg[2];
        }
        else if (batteryTimer < timeSlot * 4 && batteryTimer >= timeSlot * 3)
        {
            batteryImgCast.sprite = batterImg[1];
        }
        else // 건전지 바닥
        {
            flashLight.SetActive(false);
            onOff = false;
            batteryImgCast.sprite = batterImg[0];
        }
    }
}
