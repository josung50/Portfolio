using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Bullet : MonoBehaviour {

    //related slow bullet cam
    Transform bulletCam;
    private float timer;
    private bool timerOn;

    public AudioClip[] hitSound;
   
    //related bullet hole
    GameObject bulletHole;
    GameObject bulletHoleEffect;
    GameObject bulletBloodEffect;

    public float timeForDestroyBullet;

    // Use this for initialization
    void Start () {
        bulletCam = gameObject.transform.Find("bulletCam");
        bulletCam.gameObject.SetActive(false);
        bulletHole = Resources.Load("bullet_hole1") as GameObject;
        bulletHoleEffect = Resources.Load("bullet_holeEffect") as GameObject;
        bulletBloodEffect = Resources.Load("BloodSpurt") as GameObject;

        timerOn = false;
    }
	
	// Update is called once per frame
	void Update () {

    }

    // bullet mesh collision 충돌을 감지하면 실행되는 함수
    void OnCollisionEnter(Collision collisionObject)
    {
        Debug.Log("Bullet Collision : " + collisionObject.gameObject.tag);

        if (collisionObject.gameObject.tag == "head" || collisionObject.gameObject.tag == "body")
        {

            // 충돌체 위치에 bullet hole 생성 및 사운드 실행//
            ContactPoint point = collisionObject.contacts[0];
            Quaternion rot = Quaternion.FromToRotation(Vector3.forward, point.normal);
            Vector3 pos = point.point;
            //bulletCam.GetComponent<AudioSource>().Play();
            AudioSource.PlayClipAtPoint(hitSound[0], transform.position);
            Instantiate(bulletBloodEffect, pos, rot);
            //Instantiate(bulletHole, pos, rot);

            //blood splatter...

            //hit sound
            //bulletCam.GetComponent<AudioSource>().Play();
            AudioSource.PlayClipAtPoint(hitSound[0], transform.position);

            Time.timeScale = 1;
            Time.fixedDeltaTime = Time.timeScale * 0.02f;
        }
        else
        {
            // 충돌체 위치에 bullet hole 생성 및 사운드 실행//
            ContactPoint point = collisionObject.contacts[0];
            Quaternion rot = Quaternion.FromToRotation(Vector3.forward, point.normal);
            Vector3 pos = point.point;
            //bulletCam.GetComponent<AudioSource>().Play();
            AudioSource.PlayClipAtPoint(hitSound[0], transform.position);
            Instantiate(bulletHoleEffect, pos, rot);
            Instantiate(bulletHole, pos, rot);
        }
        timerOn = true;
        Destroy(gameObject);
    }

    // bullet collision box에서 충돌을 감지하면 실행되는 함수
    void OnTriggerEnter(Collider collisionObject)
    {
        if (collisionObject.gameObject.tag == "player")
        {

        }
        else if (collisionObject.gameObject.tag == "head")
        {
            print(collisionObject);
            bulletCam.transform.parent = null;
        }
    }
}
