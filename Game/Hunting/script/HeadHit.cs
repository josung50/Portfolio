using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HeadHit : MonoBehaviour {

	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    private void OnCollisionEnter(Collision collision)
    {
        //Debug.Log("Stag head collsion : " + collision.transform.tag);
        if (collision.gameObject.tag == "bullet7.62")
            SendMessageUpwards("HeadHit", collision);
    }
}
