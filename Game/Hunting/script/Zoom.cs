using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Zoom : MonoBehaviour {

    public float mouseSensitivityZoomX;
    public float mouseSensitivityZoomY;
    private float moveLR, rotX, rotY;
    public float minVertical = -45.0f, maxVertical = 45.0f;

    public GameObject scope;
    public GameObject mainCam;
    public GameObject riple;
    public GameObject magnificationCam;
    public GameObject lightForlens;

    private bool isZoom;
    private bool nightVision;
    public AudioClip nightVisionSound;
    Animator zoomAnimator;

    enum Magnification
    {
        one, two, four, eight
    };
    private Magnification stateMagnification;

    // 영점 조절 관련
    private int zeroPoint;
    public Text zeroPointText;
    public GameObject ShotPoint;

    private RaycastHit hit;

    public static bool headLockOn;
    public static bool bodyLockOn;
    public static float distance; // headshot 카메라 씬에 쓰이는 거리

    // Use this for initialization
    void Start () {
        ShotPoint.transform.localEulerAngles = new Vector3(-0.175f, 180f, 0);
        zeroPoint = 100;
        scope.GetComponent<Camera>().enabled = false;
        isZoom = false;
        nightVision = false;
        zoomAnimator = gameObject.GetComponent<Animator>();
    }
	
	// Update is called once per frame
	void Update () {
        if (isZoom)
        {
            if (Input.GetButtonDown("Fire2"))
            { 
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.gunIdle;
                isZoom = false;
                gameObject.GetComponent<Zoom>().enabled = false;
            }
        }
        else
        {
            if (Input.GetButtonDown("Fire2"))
            {
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.useZoom;
                isZoom = true;
            }
        }
        ZoomInOut();
        ControllMagnification();
        ControllZeroPoint();
        NightVision();

        //Debug.Log(ShootBullet.headShotBulletTIme);
        if (ShootBullet.headShotBulletTIme == false)
            LockOn();
    }

    /* 3인칭 cam off, scope cam on
     * scope cam에 따른 회전각 조절
     *  */
    void ZoomInOut()
    {
        if (isZoom)
        {
            scope.GetComponent<Camera>().enabled = true;
            mainCam.SetActive(false);
            zoomAnimator.SetBool("isZoom", true);
            mouseRotate();
            zeroPointText.enabled = true;
        }
        else
        {
            scope.GetComponent<Camera>().enabled = false;
            mainCam.SetActive(true);
            zoomAnimator.SetBool("isZoom", false);
            zeroPointText.enabled = false;
        }
    }

    void mouseRotate()
    {
        // 반동 효과
        if (ShootBullet.reboundUp)
        {
            rotY -= 0.15f;
            riple.transform.localRotation = Quaternion.Euler(-rotY, 0, 0);
        }
        else if (ShootBullet.reboundDown)
        {
            rotY += 0.15f;
            riple.transform.localRotation = Quaternion.Euler(-rotY, 0, 0);
        }
        else
        {
            TPScharacterCtrl.mouseSensitivityX = mouseSensitivityZoomX;

            //get input from mouse
            rotY -= Input.GetAxis("Mouse Y") * mouseSensitivityZoomY; // 코드 질문 -> 반전 때문에 - 줬는데 풀어버리면 고정이 되버림
            rotY = Mathf.Clamp(rotY, minVertical, maxVertical); // 수직 앵글의 범위 제한

            //rotate the camera on the Y axis , 카메라가 위 아래로 돌아간다. X축 회전
            riple.transform.localRotation = Quaternion.Euler(-rotY, 0, 0);
        }
    }

    void ControllMagnification()
    {
        if (isZoom)
        {
            if (Input.GetAxis("Mouse ScrollWheel") > 0)
            {
                stateMagnification++;
                if (stateMagnification > Magnification.eight)
                    stateMagnification = Magnification.one;
                switch (stateMagnification)
                {
                    case Magnification.one:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 30;
                        break;
                    case Magnification.two:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 15;
                        break;
                    case Magnification.four:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 8;
                        break;
                    case Magnification.eight:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 4;
                        break;
                }
            }
            else if (Input.GetAxis("Mouse ScrollWheel") < 0)
            {
                stateMagnification--;
                if (stateMagnification < Magnification.one)
                    stateMagnification = Magnification.eight;
                switch (stateMagnification)
                {
                    case Magnification.one:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 30;
                        break;
                    case Magnification.two:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 15;
                        break;
                    case Magnification.four:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 8;
                        break;
                    case Magnification.eight:
                        magnificationCam.GetComponent<Camera>().fieldOfView = 4;
                        break;
                }
            }
        }
    }

    void ControllZeroPoint()
    {
        if(Input.GetKeyDown(KeyCode.PageDown))
        {
            if (zeroPoint > 100)
                zeroPoint -= 100;
        }
        else if (Input.GetKeyDown(KeyCode.PageUp))
        {
            if (zeroPoint < 400)
                zeroPoint += 100;
        }

        switch (zeroPoint)
        {
            case 100:
                ShotPoint.transform.localEulerAngles = new Vector3(-0.175f, 180f, 0);
                //ShotPoint.transform.localEulerAngles = new Vector3(-0.45f, 180f, 0);
                break;
            case 200:
                ShotPoint.transform.localEulerAngles = new Vector3(-0.25f, 179.98f, 0);
                break;
            case 300:
                ShotPoint.transform.localEulerAngles = new Vector3(-0.32f, 179.975f, 0);
                break;
            case 400:
                ShotPoint.transform.localEulerAngles = new Vector3(-0.42f, 179.975f, 0);
                break;
        }

        zeroPointText.text = "영점 : " + zeroPoint.ToString() + "m";
    }

    // head Or body
    void LockOn()
    {
        int layerMask = 1 << 8;
        layerMask = ~layerMask;
        if (Physics.Raycast(ShotPoint.transform.position, ShotPoint.transform.forward, out hit, 1000, layerMask))
        {
            //Debug.Log(hit.transform.tag);
            if (hit.transform.tag == "head")
            {
                Debug.Log("Lock on head");
                headLockOn = true;
                bodyLockOn = false;
                distance = hit.distance;
            }
            else if (hit.transform.tag == "body")
            {
                Debug.Log("Lock on body");
                headLockOn = false;
                bodyLockOn = true;
            }
            else
            {
                headLockOn = false;
                bodyLockOn = false;
            }
        }

        if (zeroPoint == 100)
        {
            if (hit.distance < 25)
                ShotPoint.transform.localEulerAngles = new Vector3(-0.075f, 180f, 0);
            else if (hit.distance < 50 && hit.distance >= 25)
                ShotPoint.transform.localEulerAngles = new Vector3(-0.085f, 180f, 0);
            else if (hit.distance < 75 && hit.distance >= 50)
                ShotPoint.transform.localEulerAngles = new Vector3(-0.115f, 180f, 0);
            else
                ShotPoint.transform.localEulerAngles = new Vector3(-0.145f, 180f, 0);
        }
    }

    void NightVision()
    {
        if(isZoom)
        {
            if (Input.GetKeyDown(KeyCode.N))
            {
                if (nightVision == false)
                {
                    magnificationCam.GetComponent<DeferredNightVisionEffect>().enabled = true;
                    lightForlens.SetActive(true);
                    nightVision = true;
                    AudioSource.PlayClipAtPoint(nightVisionSound, gameObject.transform.position);
                }
                else
                {
                    magnificationCam.GetComponent<DeferredNightVisionEffect>().enabled = false;
                    magnificationCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier = 0;
                    lightForlens.SetActive(false);
                    nightVision = false;
                }
            }
        }
        else
        {
            magnificationCam.GetComponent<DeferredNightVisionEffect>().enabled = false;
            magnificationCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier = 0;
            lightForlens.SetActive(false);
            nightVision = false;
        }

        if (nightVision == true && magnificationCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier < 2)
        {
            magnificationCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier += Time.deltaTime;
        }
    }
}
