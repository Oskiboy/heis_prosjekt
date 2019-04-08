pipeline {
    agent { 
        dockerfile {
            filename 'Dockerfile'
            dir 'Docker'
        }
    }
    stages {
        stage('Initialization') {
            steps {
                sh """
                mkdir logs
                echo "Logs Initialized" >> logs/test.log
                git submodule init
                git submodule update
                """
            }
        }
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                make

                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('Build simulator') {
            steps {
                sh '''
                cd elevator_simulator
                ./build.sh
                ./build_wrapper.sh
                '''
            }
        }
        stage('UnitTests') {
            steps {
                sh 'mv elevator_simulator/libelev_wrapper.a tests/'
                sh 'echo "Running Unit Tests:"'
                sh 'make tests'
                sh 'echo "Tests built successfully"'
                sh '''
                echo "Running server..."
                ./elevator_simulator/build/sim_server &
                export SERVER_PID=$!
                make run_tests >> logs/test.log
                echo "Tests finished, killing server..."
                kill $SERVER_PID
                ''' 
            }
        }
    }
    post {
        success {
            sh '''
            echo "Build passed!"
            '''
        }
        failure {
            sh '''
            echo "Build failed!"
            '''
        }
        always {
            archiveArtifacts artifacts: "logs/*.log, build/heis"
            sh '''
            ls
            echo "Starting clean"
            make clean
            rm -rf build/ logs/
            '''
        }
    }
}
