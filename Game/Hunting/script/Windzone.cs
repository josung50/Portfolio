using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Windzone : MonoBehaviour {

    public bool windOn;
    private bool changeWInd;
    public float xForce;
    public float zForce;

    public Text windSpeedText;
    public Image windDirection;
    private float windSpeed;

    // Use this for initialization
    void Start () {
        windOn = true;
        changeWInd = true;
    }
	
	// Update is called once per frame
	void Update () {
        if (changeWInd)
            StartCoroutine(createWind());

        if (GameObject.FindGameObjectWithTag("bullet7.62"))
        {
            if(windOn)
                GameObject.FindGameObjectWithTag("bullet7.62").GetComponent<ConstantForce>().force = new Vector3(xForce, 0, zForce);
        }

        windSpeed = Mathf.Pow((Mathf.Pow(xForce, 2) + Mathf.Pow(zForce, 2)), 0.5f);
        windSpeedText.text = windSpeed.ToString("N3") + " m / s";

        if (xForce != 0)
        {
            float angle = -Mathf.Atan2(xForce, zForce) * Mathf.Rad2Deg;
            windDirection.rectTransform.eulerAngles = new Vector3(0, 0, angle - 45);
        }
    }

    IEnumerator createWind()
    {
        xForce = Random.Range(-0.5f, 0.5f);
        zForce = Random.Range(-0.5f, 0.5f);
        changeWInd = false;
        yield return new WaitForSecondsRealtime(Random.Range(15,30));
        changeWInd = true;
    }
}
