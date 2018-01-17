using Cinemachine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Playables;
using UnityEngine.UI;

public class ShootBullet : MonoBehaviour {

    public GameObject bulletStartPoint;

    //related shot bullet
    GameObject prefab;
    GameObject prefab2;
    GameObject bullet;
    GameObject bulletMuzzle;
    public float bulletSpeed;
    public float shotDelay = 120;
    private float shotDelayTimer;
    private bool shotPossible;
    public static bool headShotBulletTIme;
    public static bool reboundUp, reboundDown;

    public AudioClip shootSound;

    //related rebound
    public GameObject rifle;

    //related headShot
    public GameObject Cam;
    public GameObject dollyCam;
    public GameObject dollyCam2;

    // Use this for initialization
    void Start () {
        shotPossible = false;
        prefab = Resources.Load("bullet7.62") as GameObject; // 총알 불러오기
        prefab2 = Resources.Load("bulletMuzzle2") as GameObject; // 머즐 불러오기
    }
	
	// Update is called once per frame
	void Update () {
        if (TPScharacterCtrl.playerState == TPScharacterCtrl.PLAYERSTATE.useZoom)
        {
            if (Input.GetButton("Fire1"))
            {
                if (shotPossible == true && headShotBulletTIme == false)
                {
                    Fire();
                    shotPossible = false;
                }
            }
            ShootDelayCheck();
        }
    }

    void Fire()
    {
        bullet = Instantiate(prefab) as GameObject;
        bulletMuzzle = Instantiate(prefab2) as GameObject;
        bulletMuzzle.transform.parent = bulletStartPoint.transform;
        bulletMuzzle.transform.position = bulletStartPoint.transform.position;

        AudioSource.PlayClipAtPoint(shootSound, gameObject.transform.position, 0.5f);

        if(Zoom.headLockOn == true)
            StartCoroutine(HeadShot());

        // 총알의 이동
        bullet.transform.eulerAngles = new Vector3(bulletStartPoint.transform.eulerAngles.x, bulletStartPoint.transform.eulerAngles.y, 0); // 총구 방향 설정
        bullet.transform.position = bulletStartPoint.transform.position; // 총구에서 총알 생성 총구 == bulletStartPoint
        Rigidbody rb = bullet.GetComponent<Rigidbody>();
        rb.AddForce(bulletStartPoint.transform.forward * bulletSpeed, ForceMode.Impulse); // 총알 속도 조절

        StartCoroutine(Rebound());
    }

    void ShootDelayCheck()
    {
        if (shotPossible == false)
        {
            shotDelayTimer -= (Time.deltaTime + 0.5f);
            if (shotDelayTimer <= 0)
            {
                shotDelayTimer = shotDelay;
                shotPossible = true;
            }
        }
    }

    IEnumerator Rebound()
    {
        reboundUp = true;
        reboundDown = false;
        Debug.Log("reboundUP on");
        yield return new WaitForSecondsRealtime(0.01f);
        reboundUp = false;
        reboundDown = true;
        Debug.Log("reboundDown on");
        yield return new WaitForSecondsRealtime(0.01f);
        reboundUp = false;
        reboundDown = false;
        Debug.Log("rebound false");
    }

    IEnumerator HeadShot()
    {
        headShotBulletTIme = true;
        //TPScharacterCtrl.playerAnimator.SetBool("isShoot", true);
        Cam.SetActive(true);
        GameManagerParameter.Instance().cam[0].SetActive(false); // main
        GameManagerParameter.Instance().cam[1].SetActive(false); // scope
        dollyCam.GetComponent<CinemachineVirtualCamera>().Priority = 10;
        dollyCam.GetComponent<CinemachineVirtualCamera>().m_Lens.FieldOfView = 45;
        dollyCam.SetActive(true);
        dollyCam2.SetActive(true);
        dollyCam.GetComponent<CinemachineVirtualCamera>().LookAt = bullet.transform;
        dollyCam2.GetComponent<CinemachineVirtualCamera>().LookAt = bullet.transform;
        dollyCam2.GetComponent<CinemachineVirtualCamera>().Follow = bullet.transform.Find("followTarget");

        dollyCam.GetComponent<PlayableDirector>().Play();
        ExcuteSlow(0.0001f);
        yield return new WaitForSecondsRealtime(2.3f);
        // 100M 헤드샷
        if (Zoom.distance <= 200)
        {
            ExcuteSlow(0.05f);
            Time.fixedDeltaTime = 0.02F * Time.timeScale;
            dollyCam.GetComponent<CinemachineVirtualCamera>().m_Lens.FieldOfView = 2;
            yield return new WaitForSecondsRealtime(5 + (Zoom.distance / 100)*2.2f);
            Debug.Log("100m headshot");
        }
        else // 200미터 이상
        {
            dollyCam.GetComponent<CinemachineVirtualCamera>().Priority = 7;
            yield return new WaitForSecondsRealtime(0.4f);
            ExcuteSlow(0.05f);
            Time.fixedDeltaTime = 0.02F * Time.timeScale;
            yield return new WaitForSecondsRealtime(8.0f + (Zoom.distance / 100) * 2.2f);
        }
        // 초기화
        ExcuteSlow(1); Time.fixedDeltaTime = 0.02F * Time.timeScale;
        GameManagerParameter.Instance().cam[1].SetActive(true); // scope
        dollyCam.SetActive(false);  dollyCam2.SetActive(false); Cam.SetActive(false);
        headShotBulletTIme = false;

    }
        void ExcuteSlow(float slowDownStrength)
    {
        Time.timeScale = slowDownStrength; // 1 / slowDownStrength -> (1 / slowDownStrength)배 슬로우
        //Time.fixedDeltaTime = 1.0f * 0.0025f;
        //Physics.gravity = originGravity * slowDownStrength;
    }

}
