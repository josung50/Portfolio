using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class DetectBulletCollision : MonoBehaviour {

    //related fix bullet & hide
    //MeshRenderer bulletMR;
    Vector3 tempBulletPosition;

    // Use this for initialization
    void Start () {
        //bulletMR = GetComponent<MeshRenderer>();
    }
	
	// Update is called once per frame
	void Update () {
        RotationBullet();
    }

    /*
    void OnCollisionEnter(Collision collisionObject)
    {
        bulletRB.constraints = RigidbodyConstraints.FreezePosition | RigidbodyConstraints.FreezeRotation;
        bulletMR.enabled = false;
        gameObject.SendMessageUpwards("CollisionEnter", collisionObject);
    }

    void OnTriggerEnter(Collider collisionObject)
    {
        if (collisionObject.gameObject.tag == "player")
        {

        }
        else
        {
            print(collisionObject);
            gameObject.SendMessageUpwards("TriggerEnter");
        }
    }
    */

    void RotationBullet()
    {
        gameObject.transform.eulerAngles += new Vector3(0, 0, -1);
    }
}
