using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FlareGun : MonoBehaviour {

    public Rigidbody flareBullet;
    public Transform barrelEnd;
    public GameObject muzzleParticles;
    public AudioClip flareShotSound;
    public AudioClip noAmmoSound;
    public AudioClip reloadSound;
    public int bulletSpeed = 2000;

    // Update is called once per frame
    void Update()
    {
        if (Inventory.grabItem == Inventory.GRABITEM.flareGun)
        {
            if (Input.GetButtonDown("Fire1"))
            {
                if (Inventory.flareGunEA > 0)
                {
                    Shoot();
                }
                else
                {
                    //animation.Play("noAmmo");
                    AudioSource.PlayClipAtPoint(noAmmoSound, gameObject.transform.position);
                }
            }
            /*
            if (Input.GetKeyDown(KeyCode.R))
                Reload();
                */
        }
    }

    void Shoot()
    {
        Inventory.flareGunEA--;
        Inventory.InventoryInstance().flaregunEAText.text = Inventory.flareGunEA.ToString() + " / 5";
        if (Inventory.flareGunEA <= 0)
        {
            Inventory.flareGunEA = 0;
        }

        AudioSource.PlayClipAtPoint(flareShotSound, gameObject.transform.position);

        Rigidbody bulletInstance;
        bulletInstance = Instantiate(flareBullet, barrelEnd.position, barrelEnd.rotation) as Rigidbody; //INSTANTIATING THE FLARE PROJECTILE
        bulletInstance.AddForce(barrelEnd.forward * bulletSpeed, ForceMode.Force); //ADDING FORWARD FORCE TO THE FLARE PROJECTILE
        Instantiate(muzzleParticles, barrelEnd.position, barrelEnd.rotation);   //INSTANTIATING THE GUN'S MUZZLE SPARKS	

    }

    void Reload()
    {
        if (Inventory.flareGunEA == 0)
        {
            AudioSource.PlayClipAtPoint(reloadSound, gameObject.transform.position);
            Inventory.flareGunEA++;
            //animation.CrossFade("Reload");
        }

    }
}
