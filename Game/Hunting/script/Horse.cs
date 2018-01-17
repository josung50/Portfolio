using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Horse : MonoBehaviour
{
    public int idleMaxTime;
    public float walkSpeed;
    public float runSpeed;
    public float runAwayTIme;
    public GameObject runAwayTarget;

    private float timer;
    private float runAwayTimer;
    private bool timerOn;
    private bool navOn;
    private Vector3 destination;
    private NavMeshAgent nav;
    private Animator horseAnimator;
    private int idleRandomNumber;

    private AudioSource roarSound;

    public int HP;

    public enum HORSESTATE
    {
        ordinary, hit, dead, runaway
    };
    public static HORSESTATE horseState;


    // Use this for initialization
    void Start()
    {
        HP = 100;
        nav = gameObject.GetComponent<NavMeshAgent>();
        horseAnimator = GetComponent<Animator>();
        horseState = HORSESTATE.ordinary;
        roarSound = GetComponent<AudioSource>();
        idleRandomNumber = 0;
        runAwayTimer = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if (horseState == HORSESTATE.ordinary)
        {
            SelectIdelRunWalk();
            UnLockState();
        }
        else if(horseState == HORSESTATE.runaway)
        {
            RunAway();
        }
        else if(horseState == HORSESTATE.dead)
        {
        }

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
                horseAnimator.SetBool("isWalk", false);
                horseAnimator.SetBool("isRun", false);
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
        horseAnimator.SetBool("isWalk", true);
        horseAnimator.SetBool("isRun", false);
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
        horseAnimator.SetBool("isWalk", false);
        horseAnimator.SetBool("isRun", true);
        nav.speed = runSpeed;
        destination = transform.position;

        int temp = Random.Range(1, 3);
        if (temp == 1)
            destination.x = transform.position.x + 10.0f;
        else
            destination.x = transform.position.x - 10.0f;

        temp = Random.Range(1, 2);
        if (temp == 1)
            destination.z = transform.position.z + 10.0f;
        else
            destination.z = transform.position.z - 10.0f;

        nav.SetDestination(destination);
        //print(destination + "     " + transform.position);
        navOn = true;
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
    
    void RunAway()
    {
        // 이전 상태 초기화
        navOn = false;
        timerOn = false;

        //Debug.Log("Stag Start RunAway");
        nav.ResetPath();
        horseState = HORSESTATE.runaway;
        horseAnimator.SetBool("isRun", true);
        nav.speed = runSpeed;
        destination = transform.position - runAwayTarget.transform.position;
        nav.SetDestination(transform.position + destination.normalized * 5);

        if (runAwayTimer >= runAwayTIme)
        {
            nav.ResetPath();
            runAwayTimer = 0;
            horseAnimator.SetBool("isRun", false);
            horseState = HORSESTATE.ordinary;
            //Debug.Log("End RunAway");
        }
        else
            runAwayTimer += Time.deltaTime;
    }

    void HeadHit()
    {
        HP = 0;
        Debug.Log("Horse HeadHit , hp : " + HP);
        DeadCheck();
    }

    void BodyHit()
    {
        //Debug.Log("Stag BodyHit");
        HP -= 35;
        DeadCheck();
        if(horseState != HORSESTATE.dead)
            StartCoroutine(HitAfterRun());
    }

    void DeadCheck()
    {
        if(HP <= 0)
        {
            horseAnimator.SetBool("isDead", true);
            horseState = HORSESTATE.dead;
            if (GameGoal.Instance().goal[0] >= 1)
            {
                GameGoal.Instance().goal[0]--;
                GameGoal.Instance().sumGoal--;
            }
            Debug.Log("left horse : " + GameGoal.Instance().goal[0]);
        }
    }

    IEnumerator HitAfterRun()
    {
        horseAnimator.SetBool("isHit", true);
        yield return new WaitForSeconds(0.5f);
        horseAnimator.SetBool("isHit", false);
        RunAway();
    }
}
