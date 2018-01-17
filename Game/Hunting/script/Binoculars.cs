using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Binoculars : MonoBehaviour {

    public float mouseSensitivityBinocularsX;
    public float mouseSensitivityBinocularsY;

    //related zoom
    public GameObject mainCam; 
    public GameObject binoculars;
    public static bool enableBinoculars;
    private bool nightVision;
    public AudioClip nightVisionSound;
    public RaycastHit hit;

    private float timer;
    private float delayForAnimation;

    private Vector3 initMainCamPosition;

    private bool isBin;
    Animator binocularsAnimator;

    enum Magnification
    {
        one, two, four, eight
    };
    private Magnification stateMagnification;


    void Start() {
        initMainCamPosition = mainCam.transform.localPosition;
        enableBinoculars = false;
        stateMagnification = Magnification.one; // 처음 1배율
        //binocularsAnimator = gameObject.GetComponent<Animator>();
        //binocularsAnimator.SetBool("isBin", false);
        timer = 0;
    }

	// Update is called once per frame
	void Update () {
        if (Input.GetKeyDown(KeyCode.Alpha2))
        {
            if (enableBinoculars == false)
            {
                binoculars.SetActive(true);
                enableBinoculars = true;
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.useBinoculars;
                //binocularsAnimator.SetBool("isBin", true);

            }
            else
            {
                binoculars.SetActive(false);
                enableBinoculars = false;
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.gunIdle;
                //binocularsAnimator.SetBool("isBin", false);

            }

        }

        ControllMagnification();
        NightVision();
    }

    void OnGUI()
    {
        if(enableBinoculars)
        {
            TPScharacterCtrl.mouseSensitivityX = mouseSensitivityBinocularsX;
            TPScharacterCtrl.mouseSensitivityY = mouseSensitivityBinocularsY;
            
            delayForAnimation = 1.5f;
            mainCam.transform.localPosition = new Vector3(0, 2.7f, 0.75f);
            //mainCam.GetComponent<Camera>().nearClipPlane = 3.0f;
        }
        else
        {
            mainCam.transform.localPosition = initMainCamPosition;
            mainCam.GetComponent<Camera>().fieldOfView = 60;
            //timer = 0;
        }
    }
    void ControllMagnification()
    {
        if(enableBinoculars)
        {
            if (Input.GetAxis("Mouse ScrollWheel") > 0)
            {
                stateMagnification++;
                if (stateMagnification > Magnification.eight)
                    stateMagnification = Magnification.one;
                switch (stateMagnification)
                {
                    case Magnification.one:
                        mainCam.GetComponent<Camera>().fieldOfView = 60;
                        break;
                    case Magnification.two:
                        mainCam.GetComponent<Camera>().fieldOfView = 30;
                        break;
                    case Magnification.four:
                        mainCam.GetComponent<Camera>().fieldOfView = 15;
                        break;
                    case Magnification.eight:
                        mainCam.GetComponent<Camera>().fieldOfView = 8;
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
                        mainCam.GetComponent<Camera>().fieldOfView = 60;
                        break;
                    case Magnification.two:
                        mainCam.GetComponent<Camera>().fieldOfView = 30;
                        break;
                    case Magnification.four:
                        mainCam.GetComponent<Camera>().fieldOfView = 15;
                        break;
                    case Magnification.eight:
                        mainCam.GetComponent<Camera>().fieldOfView = 8;
                        break;
                }
            }
        }
    }

    void NightVision()
    {
        if (enableBinoculars)
        {
            if (Input.GetKeyDown(KeyCode.N))
            {
                if (nightVision == false)
                {
                    mainCam.GetComponent<DeferredNightVisionEffect>().enabled = true;
                    nightVision = true;
                    AudioSource.PlayClipAtPoint(nightVisionSound, gameObject.transform.position);
                }
                else
                {
                    mainCam.GetComponent<DeferredNightVisionEffect>().enabled = false;
                    nightVision = false;
                    mainCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier = 0;
                }
            }
        }
        else
        {
            mainCam.GetComponent<DeferredNightVisionEffect>().enabled = false;
            nightVision = false;
            mainCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier = 0;
        }

        if(nightVision == true && mainCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier < 2)
        {
            mainCam.GetComponent<DeferredNightVisionEffect>().m_LightSensitivityMultiplier += Time.deltaTime;
        }
    }
}
