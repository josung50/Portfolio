using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Bear : MonoBehaviour
{
    public GameObject GM;

    public int idleMaxTime;
    public float walkSpeed;
    public float runSpeed;
    public float roarTIme;
    public float chaseTime;
    public float attackTime;
    public GameObject chaseTarget;
    public float runAwayTIme;
    private float runAwayTimer;

    private float attackTimer;
    private float roarTimer;
    private float chaseTimer;
    private float chaseTimer2;
    private float timer;
    private bool timerOn;
    private bool navOn;
    private bool chaseOn;
    private Vector3 destination;
    private NavMeshAgent nav;
    private Animator bearAnimator;
    private int idleRandomNumber;
    private Vector3 startChasingPoint;

    private AudioSource roarSound;

    public enum BEARSTATE
    {
        ordinary, attack, hit, dead, chase, runaway
    };
    public static BEARSTATE bearState;


    // Use this for initialization
    void Start()
    {
        startChasingPoint = transform.position;
        nav = gameObject.GetComponent<NavMeshAgent>();
        bearAnimator = GetComponent<Animator>();
        bearState = BEARSTATE.ordinary;
        roarSound = GetComponent<AudioSource>();
        chaseOn = false;
        chaseTimer = chaseTimer2 = 0;
        roarTimer = 0;
        idleRandomNumber = 0;
        attackTimer = attackTime;

    }

    // Update is called once per frame
    void Update()
    {
        //print("currentP : " + gameObject.transform.position + "      destP : " + destination);
        //print("chaseTimer1 : " + chaseTimer + "    chaseTimer2 : " + chaseTimer2);
        //print("currentP : " + gameObject.transform.position + "      startCP : " + startChasingPoint);

        Roar();
        if (bearState == BEARSTATE.ordinary)
        {
            startChasingPoint = transform.position;
            SelectIdelRunWalk();
            UnLockState();
        }
        else if (bearState == BEARSTATE.chase)
            Chase();
    }

    void UnLockState()
    {
        if (timerOn == true)
        {
            timer += Time.deltaTime;
            if (timer > idleMaxTime)
            {
                timerOn = false;
                timer = 0;
            }
        }
        else if (navOn == true)
            if (CheckInDestination())
            {
                navOn = false;
                bearAnimator.SetBool("isWalk", false);
                bearAnimator.SetBool("isRun", false);
            }
    }
    void SelectIdelRunWalk()
    {
        if (timerOn == false && navOn == false)
        {
            int randomTemp = Random.Range(1, 4); // 내림이기 때문에 4까지
            if (randomTemp == 1) // idle 
                Idle();
            else if (randomTemp == 2) // walk
                Walk();
            else // run
                Run();
        }
    }
    void Idle()
    {
        timerOn = true;
    }

    void Walk()
    {
        bearAnimator.SetBool("isWalk", true);
        bearAnimator.SetBool("isRun", false);
        nav.speed = walkSpeed;
        destination = transform.position;

        int temp = Random.Range(1, 3);
        if (temp == 1)
            destination.x = transform.position.x + 5.0f;
        else
            destination.x = transform.position.x - 5.0f;

        temp = Random.Range(1, 2);
        if (temp == 1)
            destination.z = transform.position.z + 5.0f;
        else
            destination.z = transform.position.z - 5.0f;

        nav.SetDestination(destination);
        navOn = true;
    }

    void Run()
    {
        bearAnimator.SetBool("isWalk", false);
        bearAnimator.SetBool("isRun", true);
        nav.speed = runSpeed;
        destination = transform.position;

        int temp = Random.Range(1, 3);
        if (temp == 1)
            destination.x = transform.position.x + 15.0f;
        else
            destination.x = transform.position.x - 15.0f;

        temp = Random.Range(1, 2);
        if (temp == 1)
            destination.z = transform.position.z + 15.0f;
        else
            destination.z = transform.position.z - 15.0f;

        nav.SetDestination(destination);
        navOn = true;
    }

    void Chase()
    {
        if (chaseTimer >= chaseTime)
        {
            Debug.Log("chase off");
            ChaseOffTimer();
        }
        else
        {
            bearAnimator.SetBool("isRun", true);
            nav.speed = runSpeed;
            chaseTimer += Time.deltaTime;
            nav.SetDestination(chaseTarget.transform.position);
        }
    }
    void ChaseOffTimer() // 추격을 하지 않고 반대로 간다.
    {
        if (chaseTimer2 >= chaseTime * 1.5f)
        {
            navOn = false;
            timerOn = false;
            chaseTimer = 0;
            bearState = BEARSTATE.ordinary;
            chaseOn = false;
            bearAnimator.SetBool("isRun", false);
            GetComponent<BoxCollider>().enabled = true;
            chaseTimer2 = 0;

            AudioSource chaseSound = GM.GetComponent<AudioSource>();
            chaseSound.Stop();
        }
        else
        {
            Debug.Log("chase off2");
            destination = transform.position - chaseTarget.transform.position;
            nav.SetDestination(transform.position + destination.normalized * 5);
            //nav.SetDestination(startChasingPoint);
            nav.speed = runSpeed;
            chaseTimer2 += Time.deltaTime;
        }
    }

    // 목적지의 좌표 +-2로 설정
    bool CheckInDestination()
    {
        // 목표지점 도달
        if ((transform.position.x >= destination.x - 2.0f && transform.position.x <= destination.x + 2.0f)
            && (transform.position.z >= destination.z - 2.0f && transform.position.z <= destination.z + 2.0f))
            return true;
        else
            return false;
    }

    void Roar()
    {
        if (roarTimer > roarTIme)
        {
            roarTimer = 0;
            roarSound.Play();
        }
        else
        {
            roarTimer += Time.deltaTime;

        }
    }

    private void OnTriggerEnter(Collider other) // 플레이어 감지
    {
        if (other.tag == "flarebulletLightBox")
        {
            RunAway();
        }
        else
        {
            if (other.tag == "player")
            {
                Debug.Log("chase on");
                if (bearState == BEARSTATE.ordinary)
                {
                    //AudioSource.PlayClipAtPoint(GameManagerParameter.Instance().BackGroundSound[0], chaseTarget.transform.position, 1);
                    AudioSource chaseSound = GM.GetComponent<AudioSource>();
                    chaseSound.Play();
                    roarSound.Play();
                }
                GetComponent<BoxCollider>().enabled = false;
                bearState = BEARSTATE.chase;
            }
        }
    }

    void Attack(Collider other)
    {
        Debug.Log("bear attack");
        bearState = BEARSTATE.attack;
        bearAnimator.SetBool("isAttack", true);
        nav.enabled = false;
        HP.isHit = true;
        StartCoroutine(WaitAttack());
    }

    IEnumerator WaitAttack()
    {
        yield return new WaitForSeconds(1.5f);
        nav.enabled = true;
        bearState = BEARSTATE.chase;
        bearAnimator.SetBool("isAttack", false);
        bearAnimator.SetBool("isRun", true);
    }

    void RunAway()
    {
        // 이전 상태 초기화
        navOn = false;
        timerOn = false;

        //Debug.Log("Stag Start RunAway");
        nav.ResetPath();
        bearState = BEARSTATE.runaway;
        bearAnimator.SetBool("isRun", true);
        nav.speed = runSpeed;
        destination = transform.position - chaseTarget.transform.position;
        nav.SetDestination(transform.position + destination.normalized * 5);

        if (runAwayTimer >= runAwayTIme)
        {
            nav.ResetPath();
            runAwayTimer = 0;
            bearAnimator.SetBool("isRun", false);
            bearState = BEARSTATE.ordinary;
            //Debug.Log("End RunAway");
        }
        else
            runAwayTimer += Time.deltaTime;
    }
}
